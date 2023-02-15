#!/usr/bin/env bash
# echo "this is ft container"
# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft testvector.cpp -o FT_CONTAINER ; ./FT_CONTAINER ; rm FT_CONTAINER
# echo "this is std containter" 
# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std testvector.cpp -o STD_CONTAINER; ./STD_CONTAINER ; rm STD_CONTAINER

c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft testvector.cpp -o FT_CONTAINER ; ./FT_CONTAINER > ft_result; rm FT_CONTAINER 

c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std testvector.cpp -o STD_CONTAINER; ./STD_CONTAINER > std_result; rm STD_CONTAINER

diff  ft_result std_result 
