#include <iostream>
#include <map>

#include <boost/math/special_functions/factorials.hpp>

#include <my_allocator.h>
#include <my_vector.h>

template<class T>
uint32_t my::allocator<T>::opts::preloc_n = 10;
template<class T>
bool my::allocator<T>::opts::extendable = false;
template<class T>
uint32_t my::allocator<T>::opts::extloc_n = 5;

int main(int, char**)
{
	// - �������� ���������� std::map<int, int>
	std::map<int, int> map_int_int;

	// - ���������� 10 ����������, ��� ���� - ��� ����� �� 0 �� 9, � �������� - ��������� �����
	for (int i = 0; i <= 9; ++i)
	{
		map_int_int.insert({ i, static_cast<int>(boost::math::factorial<float>(i)) });
	}

	// - �������� ���������� std::map<int, int> � ����� �����������, ������������ 10 ����������
	std::map<int, int, std::less<int>, my::allocator<std::pair<const int, int>>>  map_int_int_myalloc;

	// - ���������� 10 ����������, ��� ���� - ��� ����� �� 0 �� 9, � �������� - ��������� �����
	for (int i = 0; i <= 9; ++i)
	{
		if (i == 9)
		{
			try
			{
				map_int_int.insert({ i, static_cast<int>(boost::math::factorial<float>(i)) });
			}
			catch (const std::bad_alloc&)
			{
				//!!! map allocated 1 element in default consructor
			}
		}
		else
		{
			map_int_int_myalloc.insert({ i, static_cast<int>(boost::math::factorial<float>(i)) });
		}
	}

	// - ����� �� ����� ���� ��������(���� � �������� ��������� ��������) ���������� � ����������
	for (const auto& [key, value] : map_int_int_myalloc)
	{
		std::cout << key << " " << value << std::endl;
	}

	// - �������� ���������� ������ ���������� ��� �������� �������� ���� int
	my::vector<int> vect_int;

	// - ���������� 10 ���������� �� 0 �� 9
	for (int i = 0; i <= 9; ++i)
	{
		vect_int.push_back(i);
	}

	// - �������� ���������� ������ ���������� ��� �������� �������� ���� int � ����� �����������, ������������ 10 ����������
	my::vector<int, my::allocator<int>> vect_int_myalloc;

	// - ���������� 10 ���������� �� 0 �� 9
	for (int i = 0; i <= 9; ++i)
	{
		try
		{
			vect_int_myalloc.push_back(i);
		}
		catch (const std::bad_alloc&)
		{
			//capacity 10 maximum
		}
	}

	// - ����� �� ����� ���� ��������, ���������� � ����������
	for (my::vector<int, my::allocator<int>>::const_iterator i = vect_int_myalloc.cbegin(); i != vect_int_myalloc.cend(); ++i)
	{
		std::cout << *i << std::endl;
	}

	return 0;
}