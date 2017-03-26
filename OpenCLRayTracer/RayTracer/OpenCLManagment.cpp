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

int OpenCLManagment::runOpenCL()
{
	//Initalise Clew
	bool clpresent = 0 == clewInit();
	if (!clpresent)
	{
		throw std::runtime_error("OpenCL library not found");
	}

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	char string[MEM_SIZE];

	std::string loadedOpenCLFile = OpenCLManagment::loadOpenCLFile("Assets/cl/helloworld.cl");

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

	/* Create OpenCL context */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* Create Command Queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	/* Create Memory Buffer */
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);

	const char* constLoadedCLFile = loadedOpenCLFile.c_str();

	/* Create Kernel Program from the source */
	program = clCreateProgramWithSource(context, 1, &constLoadedCLFile, NULL, &ret);

	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* Create OpenCL Kernel */
	kernel = clCreateKernel(program, "hello", &ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

	/* Execute OpenCL Kernel */
	ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
		MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

	/* Display Result */
	std::cout << string << std::endl;

	/* Finalization */
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memobj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	return 0;
}