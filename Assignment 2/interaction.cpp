#include "interaction.h"


void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods ){
	if ( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE ){
		std::cout << "Right button pressed" << std::endl;
		
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE ){
        std::cout << "Left button pressed" << std::endl;
        
    }
}
