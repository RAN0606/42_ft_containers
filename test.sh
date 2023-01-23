#!/usr/bin/env bash

# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft test.cpp -o FT_CONTAINER ; ./FT_CONTAINER ; rm FT_CONTAINER
# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std test.cpp -o STD_CONTAINER; ./STD_CONTAINER ; rm STD_CONTAINER
# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft test.cpp -o FT_CONTAINER ; ./FT_CONTAINER > ft_result; rm FT_CONTAINER

# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std test.cpp -o STD_CONTAINER; ./STD_CONTAINER > std_result; rm STD_CONTAINER

# diff std_result ft_result
c++ -std=c++98 -Wall -Wextra -Werror  ./containers_test/srcs/vector/assign.cpp -o FT_CONTAINER ; ./FT_CONTAINER ; rm FT_CONTAINER