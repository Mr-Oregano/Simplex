
#include "Introduction.h"

#include <iostream>

namespace Simplex
{

	void Introduce(void)
	{

		std::cout << "Welcome to the Simplex Game Engine!" << std::endl;

		#ifdef SMPX_CONFIG_DEBUG

			std::cout << "Running SMPX_CONFIG_DEBUG..." << std::endl;

		#elif defined SMPX_CONFIG_RELEASE

			std::cout << "Running SMPX_CONFIG_RELEASE..." << std::endl;

		#elif defined SMPX_CONFIG_DIST

			std::cout << "Running SMPX_CONFIG_DIST..." << std::endl;

		#endif
	
	}

}