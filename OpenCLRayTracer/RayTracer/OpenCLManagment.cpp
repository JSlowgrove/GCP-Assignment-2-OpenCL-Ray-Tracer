#include "OpenCLManagment.h"

#include <fstream>
#include "../Core/Utilities.h"

std::string OpenCLManagment::loadOpenCLFile(std::string fileName)
{
	//file loading message
	Utilities::logI("Loading " + fileName);

	//The loaded file as a string
	std::string loadedFile;

	//Open the file using a ifstream
	std::ifstream file(fileName);

	//If the file successfully opens
	if (file.is_open())
	{
		//File loading variables
		std::string currentLine;

		//While there are still lines to be read in from the file
		while (getline(file, currentLine))
		{
			//Add the current line to the loaded file
			loadedFile.append(currentLine);

			//Add a new line symbol to the end of the line
			loadedFile.append("\n");
		}
		//Close the file
		file.close();

		//file loaded message
		Utilities::logI(fileName + " loaded");
	}
	//If the file could not be opened then output error message
	else
	{
		Utilities::logI("Unable to open file");
	}

	//Return the loaded file as a std::string
	return loadedFile;
}


std::vector<int> OpenCLManagment::runOpenCLRayTrace(unsigned int numberOfBoxes, glm::vec4 rayDirection,	std::vector<glm::vec4> vertices, 
	std::vector<glm::vec4> colours, std::vector<glm::vec4> rayOrigins, int verticiesSize, int coloursSize, int originsSize, int numberOfRays)
{
	std::vector<int> pixels;

	//Initalise Clew
	bool clpresent = 0 == clewInit();
	if (!clpresent)
	{
		throw std::runtime_error("OpenCL library not found");
	}

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memVerticies = NULL;
	cl_mem memColours = NULL;
	cl_mem memOrigins = NULL;
	cl_mem memPixels = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	std::string loadedOpenCLFile = OpenCLManagment::loadOpenCLFile("Assets/cl/raytrace.cl");

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to get platform ID, Error: " + std::to_string(ret));
	}

	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to get device ID, Error: " + std::to_string(ret));
	}

	/* Create OpenCL context */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* Create Command Queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	/* Create Memory Buffers */
	memVerticies = clCreateBuffer(context, CL_MEM_READ_WRITE, verticiesSize * sizeof(glm::vec4), NULL, &ret);
	memColours = clCreateBuffer(context, CL_MEM_READ_WRITE, coloursSize * sizeof(glm::vec4), NULL, &ret);
	memOrigins = clCreateBuffer(context, CL_MEM_READ_WRITE, originsSize * sizeof(glm::vec4), NULL, &ret);
	memPixels = clCreateBuffer(context, CL_MEM_READ_WRITE, (numberOfRays * 4) * sizeof(int), NULL, &ret);

	/* Create Kernel Program from the source */
	const char* constLoadedCLFile = loadedOpenCLFile.c_str();
	program = clCreateProgramWithSource(context, 1, &constLoadedCLFile, NULL, &ret);

	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Error Building Program");
		char buildLog[20000];
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 20000, &buildLog, NULL);
		Utilities::logE(std::string(buildLog));
	}	

	/* Create OpenCL Kernel */
	kernel = clCreateKernel(program, "RayTrace", &ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel, 0, sizeof(unsigned int), (void *)&numberOfBoxes);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Number of Boxes buffer failed to initalise, Error: " + std::to_string(ret));
	}

	ret = clSetKernelArg(kernel, 1, sizeof(glm::vec4), (void *)&rayDirection);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Ray Direction buffer failed to initalise, Error: " + std::to_string(ret));
	}

	ret = clSetKernelArg(kernel, 2, sizeof(memVerticies), (void *)&memVerticies);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Verticies buffer failed to initalise, Error: " + std::to_string(ret));
	}

	ret = clSetKernelArg(kernel, 3, sizeof(memColours), (void *)&memColours);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Colours buffer failed to initalise, Error: " + std::to_string(ret));
	}

	ret = clSetKernelArg(kernel, 4, sizeof(memOrigins), (void *)&memOrigins);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Origins buffer failed to initalise, Error: " + std::to_string(ret));
	}

	ret = clSetKernelArg(kernel, 5, sizeof(memPixels), (void *)&memPixels);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Pixels buffer failed to initalise, Error: " + std::to_string(ret));
	}

	ret = clEnqueueWriteBuffer(command_queue, memVerticies, CL_TRUE, 0, 
		verticiesSize * sizeof(glm::vec4), &vertices[0], 0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to write Vertices, Error: " + std::to_string(ret));
	}

	ret = clEnqueueWriteBuffer(command_queue, memColours, CL_TRUE, 0,
		coloursSize * sizeof(glm::vec4), &colours[0], 0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to write Colours, Error: " + std::to_string(ret));
	}

	ret = clEnqueueWriteBuffer(command_queue, memOrigins, CL_TRUE, 0,
		originsSize * sizeof(glm::vec4), &rayOrigins[0], 0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to write Origins, Error: " + std::to_string(ret));
	}

	/* Execute OpenCL Kernel */
	size_t globalWorkSize = numberOfRays;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &globalWorkSize, NULL, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to set ND Range kernal, Error: " + std::to_string(ret));
	}

	/* Copy results from the memory buffer */
	int* tempPixels = (int*)clEnqueueMapBuffer(command_queue, memPixels, CL_TRUE, CL_MAP_READ, 0,
		(numberOfRays * 4) * sizeof(int), 0, NULL, NULL, &ret);

	for (unsigned int i = 0; i < (numberOfRays * 4); i++)
	{
		pixels.push_back(tempPixels[i]);
	}
	
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Error reading data");
	}

	/* Finalization */
	ret = clFlush(command_queue);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to flush command queue: " + std::to_string(ret));
	}
	ret = clFinish(command_queue);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to finish command queue: " + std::to_string(ret));
	}
	ret = clReleaseKernel(kernel);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release kernal: " + std::to_string(ret));
	}
	ret = clReleaseProgram(program);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release program: " + std::to_string(ret));
	}
	ret = clReleaseMemObject(memVerticies);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release verticies: " + std::to_string(ret));
	}
	ret = clReleaseMemObject(memColours);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release colours: " + std::to_string(ret));
	}
	ret = clReleaseMemObject(memOrigins);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release origins: " + std::to_string(ret));
	}
	ret = clReleaseMemObject(memPixels);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release pixels: " + std::to_string(ret));
	}
	ret = clReleaseCommandQueue(command_queue);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release command queue: " + std::to_string(ret));
	}
	ret = clReleaseContext(context);
	if (ret != CL_SUCCESS)
	{
		Utilities::logE("Failed to release content: " + std::to_string(ret));
	}

	return pixels;
}

// int OpenCLManagment::runOpenCLHelloWorld()
// {
// 	//Initalise Clew
// 	bool clpresent = 0 == clewInit();
// 	if (!clpresent)
// 	{
// 		throw std::runtime_error("OpenCL library not found");
// 	}
// 
// 	cl_device_id device_id = NULL;
// 	cl_context context = NULL;
// 	cl_command_queue command_queue = NULL;
// 	cl_mem memobj = NULL;
// 	cl_program program = NULL;
// 	cl_kernel kernel = NULL;
// 	cl_platform_id platform_id = NULL;
// 	cl_uint ret_num_devices;
// 	cl_uint ret_num_platforms;
// 	cl_int ret;
// 
// 	char string[MEM_SIZE];
// 
// 	std::string loadedOpenCLFile = OpenCLManagment::loadOpenCLFile("Assets/cl/helloworld.cl");
// 
// 	/* Get Platform and Device Info */
// 	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
// 	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
// 
// 	/* Create OpenCL context */
// 	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
// 
// 	/* Create Command Queue */
// 	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
// 
// 	/* Create Memory Buffer */
// 	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);
// 
// 	const char* constLoadedCLFile = loadedOpenCLFile.c_str();
// 
// 	/* Create Kernel Program from the source */
// 	program = clCreateProgramWithSource(context, 1, &constLoadedCLFile, NULL, &ret);
// 
// 	/* Build Kernel Program */
// 	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
// 
// 	/* Create OpenCL Kernel */
// 	kernel = clCreateKernel(program, "hello", &ret);
// 
// 	/* Set OpenCL Kernel Parameters */
// 	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
// 
// 	/* Execute OpenCL Kernel */
// 	ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
// 
// 	/* Copy results from the memory buffer */
// 	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
// 		MEM_SIZE * sizeof(char), string, 0, NULL, NULL);
// 
// 	/* Display Result */
// 	std::cout << string << std::endl;
// 
// 	/* Finalization */
// 	ret = clFlush(command_queue);
// 	ret = clFinish(command_queue);
// 	ret = clReleaseKernel(kernel);
// 	ret = clReleaseProgram(program);
// 	ret = clReleaseMemObject(memobj);
// 	ret = clReleaseCommandQueue(command_queue);
// 	ret = clReleaseContext(context);
// 
// 	return 0;
// }