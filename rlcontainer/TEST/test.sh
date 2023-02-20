#!/usr/bin/env bash

# echo "this is ft container"

# echo "this is std containter"
# echo "this is ft container"
# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft testvector.cpp -o FT_CONTAINER ; ./FT_CONTAINER ; rm FT_CONTAINER
# echo "this is std containter" 
# c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std testvector.cpp -o STD_CONTAINER; ./STD_CONTAINER ; rm STD_CONTAINER
echo FT_VECTOR
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft testvector.cpp -o FT_CONTAINER ; time ./FT_CONTAINER > ft_result; rm FT_CONTAINER 
echo STD_VECTOR
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std testvector.cpp -o STD_CONTAINER; time ./STD_CONTAINER > std_result; rm STD_CONTAINER
diff  ft_result std_result 

echo FT_MAP
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft testmap.cpp -o FT_CONTAINER ; time  ./FT_CONTAINER > ft_result; rm FT_CONTAINER 
echo STD_MAP
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std testmap.cpp -o STD_CONTAINER; time ./STD_CONTAINER > std_result;rm STD_CONTAINER
diff  ft_result std_result 

echo FT_STACK
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft teststack.cpp -o FT_CONTAINER ;  time ./FT_CONTAINER > ft_result; rm FT_CONTAINER 
echo STD_STACK
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std teststack.cpp -o STD_CONTAINER; time ./STD_CONTAINER > std_result; rm STD_CONTAINER
diff  ft_result std_result 
echo FT_SET
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft testset.cpp -o FT_CONTAINER ;  time ./FT_CONTAINER > ft_result; rm FT_CONTAINER 
echo STD_SET
c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESPACE=std testset.cpp -o STD_CONTAINER; time ./STD_CONTAINER > std_result; rm STD_CONTAINER
diff  ft_result std_result 
rm ft_result std_result
 