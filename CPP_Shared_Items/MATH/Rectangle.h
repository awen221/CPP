#pragma once

#include "Point_Template.h"

namespace MATH
{
	template<class T>
	class Rectangle
	{
	private:

	public:
		Rectangle() {};
		Rectangle(const T& left, const T& top, const T& right, const T& bottom) 
			:Left(left), Top(top), Right(right), Bottom(bottom) {}
		Rectangle(const Point_Template<T>& lt, const Point_Template<T>& rb)
			:Left(lt.X), Top(lt.Y), Right(rb.X), Bottom(rb.Y) {}
		Rectangle(const Point_Template<T>& lt, T Width, T Height)
		{

		}
		~Rectangle() {};

		T Left;
		T Top;
		T Right;
		T Bottom;


		
	};
}

