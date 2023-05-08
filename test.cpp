#include<iostream>

int main(){
	int list[] = {10, 20, 30};
	int num = 0;
	std::cout << list[++num] << std::endl;
	std::cout << num << std::endl;
	return 0;
}