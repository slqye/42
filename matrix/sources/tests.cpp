#include "commons.hpp"
#include "class/vector/Vector.tpp"
#include "class/matrix/Matrix.tpp"
#include "class/fn/Fn_01.tpp"
#include "class/fn/Fn_02.tpp"
#include "class/fn/Fn_04.tpp"
#include "class/fn/Fn_05.tpp"
#include "class/fn/Fn_06.tpp"
#include "class/fn/Fn_14.tpp"
#include "class/complex/Complex.tpp"

void _00(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << "for vectors:" << std::endl;
	{
		std::vector<int> add = {1, 3, 1};
		std::vector<int> sub = {10, 2, 7};
	
		Vector<int> _result(3, 0);
		Vector<int> _reshaped(4, 1);
		Vector<int> _add(add);
		Vector<int> _sub(sub);
		unsigned int _scl = 2;
		
		std::cout << "default:" << std::endl;
		std::cout << " - shape: (" << _result.get_shape().first << ", " << _result.get_shape().second << ")" << std::endl;
		std::cout << " - value:\n" << _result << std::endl;
		std::cout << std::endl;
	
		_result.add(_add);
		std::cout << "add({1, 3, 1}):\n" << _result << "\n" << std::endl;
		_result.sub(_sub);
		std::cout << "sub({10, 2, 7}):\n" << _result << "\n" << std::endl;
		_result.scl(_scl);
		std::cout << "scl(2):\n" << _result << std::endl;
		Matrix<int> reshaped = _reshaped.reshape(2, 2);
		std::cout << "reshape():\n" << reshaped << std::endl;
	
		std::cout << "\nTry catch blocks:" << std::endl;
	
		try
		{
			std::cout << _result[2] << std::endl;
			std::cout << _result[3] << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	
		try
		{
			Vector<int> _e1(4, 0);
			Vector<int> _e2(3, 0);
	
			_e1.add(_e2);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	
		try
		{
			Matrix<int> reshaped = _reshaped.reshape(2, 5);
			std::cout << "reshape():\n" << reshaped << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\n------\nfor matrices:" << std::endl;
	{
		std::vector<float> add = {1, 3, 1, 5, 7, 1, 2, 15, 48};
		std::vector<float> sub = {0, 10, -4, 9, 7, -1, 14, 6, 3};
	
		Matrix<float> _result(9, 0, 3, 3);
		Matrix<float> _add(add, 3, 3);
		Matrix<float> _sub(sub, 3, 3);
		float _scl = 2;
		
		std::cout << "default:" << std::endl;
		std::cout << " - shape: (" << _result.get_shape().first << ", " << _result.get_shape().second << ")" << std::endl;
		std::cout << " - value:\n" << _result << std::endl;
		std::cout << std::endl;
	
		_result.add(_add);
		std::cout << "add({1, 3, 1, 5, 7, 1, 2, 15, 48}):\n" << _result << "\n" << std::endl;
		_result.sub(_sub);
		std::cout << "sub({0, 10, -4, 9, 7, -1, 14, 6, 3}):\n" << _result << "\n" << std::endl;
		_result.scl(_scl);
		std::cout << "scl(2):\n" << _result << std::endl;
		Vector<float> reshaped = _result.reshape();
		std::cout << "reshape():\n" << reshaped << std::endl;

		std::cout << "\nTry catch blocks:" << std::endl;
	
		try
		{
			std::cout << _result[{2, 2}] << std::endl;
			std::cout << _result[{2, 3}] << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	
		try
		{
			Matrix<int> _error(9, 0, 4, 3);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void _01(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::vector<Vector<float>> vectors = {Vector<float>(std::vector<float>({1, 0, 0})), Vector<float>(std::vector<float>({0, 1, 0})), Vector<float>(std::vector<float>({0, 0, 1}))};
	std::vector<float> scalars = {10, -2, 0.5f};
	std::cout << Fn<float>::linear_combination(vectors, scalars) << std::endl << std::endl;

	std::vector<Vector<int>> _vectors = {Vector<int>(std::vector<int>({1, 2, 3})), Vector<int>(std::vector<int>({0, 10, -100}))};
	std::vector<int> _scalars = {10, -2};
	std::cout << Fn<int>::linear_combination(_vectors, _scalars) << std::endl;
}

void _02(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << Fn<float>::lerp(5, 10, 0.5) << std::endl;
	std::cout << Fn<float>::lerp(21, 42, 0.3) << std::endl;

	std::cout << Fn<float>::lerp(
		Vector<float>(std::vector<float>({2, 1})),
		Vector<float>(std::vector<float>({4, 2})),
		0.3)
		<< std::endl;

	std::cout << "\nTry catch blocks:" << std::endl;

	try
	{
		std::cout << Fn<float>::lerp(5, 10, 2) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n------\nfor matrices:" << std::endl;

	std::cout << Fn<float>::lerp(10, 12, 0.5) << std::endl;
	std::cout << Fn<float>::lerp(28, 53, 0.3) << std::endl;

	std::cout << Fn<float>::lerp(
		Matrix<float>(std::vector<float>({2, 1, 3, 4}), 2, 2),
		Matrix<float>(std::vector<float>({20, 10, 30, 40}), 2, 2),
		0.5)
		<< std::endl;

	std::cout << "\nTry catch blocks:" << std::endl;

	try
	{
		std::cout << Fn<float>::lerp(8, 10, -1) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void _03(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Vector<int> a(std::vector<int>({0, 0}));
	Vector<int> b(std::vector<int>({1, 1}));
	Vector<int> c(std::vector<int>({1, 1}));
	Vector<int> d(std::vector<int>({1, 1}));
	Vector<int> e(std::vector<int>({-1, 6}));
	Vector<int> f(std::vector<int>({3, 2}));

	std::cout << a.dot(b) << std::endl;
	std::cout << c.dot(d) << std::endl;
	std::cout << e.dot(f) << std::endl;

	std::cout << "\nTry catch blocks:" << std::endl;

	try
	{
		Vector<int> g(std::vector<int>({3, 2, 3}));
		std::cout << a.dot(g) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void _04(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Vector<float> a(std::vector<float>({0, 0}));
	Vector<float> b(std::vector<float>({1, 1}));
	Vector<float> c(std::vector<float>({-1, 6}));
	Vector<float> d(std::vector<float>({3, 2, 5, 9}));

	std::cout << a << std::endl;
	std::cout << a.norm_1() << " " << a.norm() << " " << a.norm_inf() << std::endl;
	std::cout << b << std::endl;
	std::cout << b.norm_1() << " " << b.norm() << " " << b.norm_inf() << std::endl;
	std::cout << c << std::endl;
	std::cout << c.norm_1() << " " << c.norm() << " " << c.norm_inf() << std::endl;
	std::cout << d << std::endl;
	std::cout << d.norm_1() << " " << d.norm() << " " << d.norm_inf() << std::endl;
}

void _05(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Vector<float> a(std::vector<float>({1, 0}));
	Vector<float> b(std::vector<float>({1, 0}));

	Vector<float> c(std::vector<float>({1, 2, 3}));
	Vector<float> d(std::vector<float>({4, 5, 6}));

	std::cout << a << "\n-\n" << b << std::endl;
	std::cout << Fn<float>::angle_cos(a, b) << std::endl << std::endl;
	std::cout << c << "\n-\n" << d << std::endl;
	std::cout << Fn<float>::angle_cos(c, d) << std::endl;

	std::cout << "\nTry catch blocks:" << std::endl;


	try
	{
		std::cout << Fn<float>::angle_cos(a, c) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void _06(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Vector<float> a(std::vector<float>({0, 0, 1}));
	Vector<float> b(std::vector<float>({1, 0, 0}));

	Vector<float> c(std::vector<float>({1, 2, 3}));
	Vector<float> d(std::vector<float>({4, 5, 6}));

	Vector<float> e(std::vector<float>({4, 2, -3}));
	Vector<float> f(std::vector<float>({-2, -5, 16}));

	std::cout << Fn<float>::cross_product(a, b) << std::endl << std::endl;
	std::cout << Fn<float>::cross_product(c, d) << std::endl << std::endl;
	std::cout << Fn<float>::cross_product(e, f) << std::endl;
}

void _07(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({1, 0, 0, 1}), 2, 2);
	Vector<float> b(std::vector<float>({4, 2}));
	
	Matrix<float> c(std::vector<float>({2, 0, 0, 2}), 2, 2);

	Matrix<float> d(std::vector<float>({2, -2, -2, 2}), 2, 2);

	Matrix<float> e(std::vector<float>({2, 1, 4, 2}), 2, 2);

	Matrix<float> f(std::vector<float>({3, -5, 6, 8}), 2, 2);
	Matrix<float> g(std::vector<float>({2, 1, 4, 2}), 2, 2);

	Matrix<float> h(std::vector<float>({
		1, 2, 3,
		4, 5, 6
	}),
	2, 3);
	Matrix<float> i(std::vector<float>({
		7, 8,
		9, 10,
		11, 12
	}),
	3, 2);
	
	std::cout << a.mul_vec(b) << std::endl << std::endl;
	std::cout << c.mul_vec(b) << std::endl << std::endl;
	std::cout << d.mul_vec(b) << std::endl << std::endl;
	std::cout << a.mul_mat(e) << std::endl << std::endl;
	std::cout << f.mul_mat(g) << std::endl << std::endl;
	std::cout << h.mul_mat(i) << std::endl << std::endl;
	std::cout << i.mul_mat(h) << std::endl;
}

void _08(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({
		1, 0,
		0, 1
	}),
	2, 2);
	Matrix<float> b(std::vector<float>({
		2, -5, 0,
		4, 3, 7,
		-2, 3, 4
	}),
	3, 3);
	Matrix<float> c(std::vector<float>({
		-2, -8, 4,
		1, -23, 4,
		0, 6, 4
	}),
	3, 3);

	std::cout << a << a.trace() << std::endl << std::endl;
	std::cout << b << b.trace() << std::endl << std::endl;
	std::cout << c << c.trace() << std::endl;

	std::cout << "\nTry catch blocks:" << std::endl;

	try
	{
		Matrix<float> d(std::vector<float>({1, 0}), 1, 2);
		std::cout << d << d.trace() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void _09(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({
		1, 0,
		0, 1
	}),
	2, 2);
	Matrix<float> b(std::vector<float>({
		2, -5, 0,
		4, 3, 7,
		-2, 3, 4
	}),
	3, 3);
	Matrix<float> c(std::vector<float>({
		-2, -8, 4,
		1, -23, 4,
		0, 6, 4
	}),
	3, 3);
	Matrix<float> d(std::vector<float>({
		7, 8,
		9, 10,
		11, 12
	}),
	3, 2);
	Matrix<float> e(std::vector<float>({
		1, 2, 3,
		4, 5, 6
	}),
	2, 3);

	std::cout << a << "\n--\n" << a.transpose() << std::endl << std::endl;
	std::cout << b << "\n--\n" << b.transpose() << std::endl << std::endl;
	std::cout << c << "\n--\n" << c.transpose() << std::endl << std::endl;
	std::cout << d << "\n--\n" << d.transpose() << std::endl << std::endl;
	std::cout << e << "\n--\n" << e.transpose() << std::endl;
}

void _10(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	}),
	3, 3);
	Matrix<float> b(std::vector<float>({
		1, 2,
		3, 4
	}),
	2, 2);
	Matrix<float> c(std::vector<float>({
		1, 2,
		2, 4
	}),
	2, 2);
	Matrix<float> d(std::vector<float>({
		8, 5, -2, 4, 28,
		4, 2.5, 20, 4, -4,
		8, 5, 1, 4, 17
	}),
	3, 5);
	Matrix<float> e(std::vector<float>({
		2, 3, 4, 5,
		9, 1, 4, 5,
		2, 3, 6, 5,
		0, 3, 6, 5,
	}),
	4, 4);

	std::cout << a << "\n-\n" << a.row_echelon() << "\n----\n" << std::endl;
	std::cout << b << "\n-\n" << b.row_echelon() << "\n----\n" << std::endl;
	std::cout << c << "\n-\n" << c.row_echelon() << "\n----\n" << std::endl;
	std::cout << d << "\n-\n" << d.row_echelon() << "\n----\n" << std::endl;
	std::cout << e << "\n-\n" << e.row_echelon() << "\n----\n" << std::endl;
}

void _11(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({
		1, -1,
		-1, 1
	}),
	2, 2);
	Matrix<float> b(std::vector<float>({
		2, 0, 0,
		0, 2, 0,
		0, 0, 2
	}),
	3, 3);
	Matrix<float> c(std::vector<float>({
		8, 5, -2,
		4, 7, 20,
		7, 6, 1
	}),
	3, 3);
	Matrix<float> d(std::vector<float>({
		8, 5, -2, 4,
		4, 2.5, 20, 4,
		8, 5, 1, 4,
		28, -4, 17, 1
	}),
	4, 4);

	std::cout << a << "\n-\n" << a.determinant() << "\n----\n" << std::endl;
	std::cout << b << "\n-\n" << b.determinant() << "\n----\n" << std::endl;
	std::cout << c << "\n-\n" << c.determinant() << "\n----\n" << std::endl;
	std::cout << d << "\n-\n" << d.determinant() << "\n----\n" << std::endl;
}

void _12(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	}),
	3, 3);
	Matrix<float> b(std::vector<float>({
		2, 0, 0,
		0, 2, 0,
		0, 0, 2
	}),
	3, 3);
	Matrix<float> c(std::vector<float>({
		8, 5, -2,
		4, 7, 20,
		7, 6, 1
	}),
	3, 3);

	std::cout << a << "\n-\n" << a.inverse() << "\n----\n" << std::endl;
	std::cout << b << "\n-\n" << b.inverse() << "\n----\n" << std::endl;
	std::cout << c << "\n-\n" << c.inverse() << "\n----\n" << std::endl;
}

void _13(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	Matrix<float> a(std::vector<float>({
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	}),
	3, 3);
	Matrix<float> b(std::vector<float>({
		2, 0, 0,
		0, 2, 0,
		0, 0, 2
	}),
	3, 3);
	Matrix<float> c(std::vector<float>({
		8, 5, -2,
		4, 7, 20,
		7, 6, 1
	}),
	3, 3);
	Matrix<float> d(std::vector<float>({
		1, -1,
		-1, 1
	}),
	2, 2);
	Matrix<float> e(std::vector<float>({
		8, 5, -2, 4, 28,
		4, 2.5, 20, 4, -4,
		8, 5, 1, 4, 17
	}),
	3, 5);

	std::cout << a << "\n-\n" << a.row_echelon() << "\n-\n" << a.rank() << "\n----\n" << std::endl;
	std::cout << b << "\n-\n" << b.row_echelon() << "\n-\n" << b.rank() << "\n----\n" << std::endl;
	std::cout << c << "\n-\n" << c.row_echelon() << "\n-\n" << c.rank() << "\n----\n" << std::endl;
	std::cout << d << "\n-\n" << d.row_echelon() << "\n-\n" << d.rank() << "\n----\n" << std::endl;
	std::cout << e << "\n-\n" << e.row_echelon() << "\n-\n" << e.rank() << "\n----\n" << std::endl;
}

void _14(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << Fn<float>::projection(90.0f, 16.0f/9.0f, 0.1f, 100.0f) << std::endl;
}

void _15(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::cout << "for vectors:" << std::endl;
	{
		std::vector<Complex> add = {Complex(1, 2), Complex(3, 4), Complex(5, 6)};
		std::vector<Complex> sub = {Complex(-2, 1), Complex(-3, 6), Complex(7, -5)};
	
		Vector<Complex> _result(3, Complex());
		Vector<Complex> _reshaped(4, Complex());
		Vector<Complex> _add(add);
		Vector<Complex> _sub(sub);
		Complex _scl(2, 0);
		
		std::cout << "default:" << std::endl;
		std::cout << " - shape: (" << _result.get_shape().first << ", " << _result.get_shape().second << ")" << std::endl;
		std::cout << " - value:\n" << _result << std::endl;
		std::cout << std::endl;
	
		_result.add(_add);
		std::cout << "add({Complex(1, 2), Complex(3, 4), Complex(5, 6)}):\n" << _result << "\n" << std::endl;
		_result.sub(_sub);
		std::cout << "sub({Complex(-2, 1), Complex(-3, 6), Complex(7, -5)}):\n" << _result << "\n" << std::endl;
		_result.scl(_scl);
		std::cout << "scl(2):\n" << _result << std::endl;
		Matrix<Complex> reshaped = _reshaped.reshape(2, 2);
		std::cout << "reshape():\n" << reshaped << std::endl;
	
		std::cout << "\nTry catch blocks:" << std::endl;
	
		try
		{
			std::cout << _result[2] << std::endl;
			std::cout << _result[3] << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	
		try
		{
			Vector<Complex> _e1(4, Complex());
			Vector<Complex> _e2(3, Complex());
	
			_e1.add(_e2);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	
		try
		{
			Matrix<Complex> reshaped = _reshaped.reshape(2, 5);
			std::cout << "reshape():\n" << reshaped << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\n------\nfor matrices:" << std::endl;
	{
		std::vector<Complex> add = {Complex(1, 2), Complex(4, 6), Complex(-5, 7), Complex(8, 12), Complex(0, 2), Complex(), Complex(2, 1), Complex(6, -3), Complex(-11, 5)};
		std::vector<Complex> sub = {Complex(-5, 9), Complex(8, 7), Complex(15, 2), Complex(13, 0), Complex(7, 4), Complex(), Complex(), Complex(3, 1), Complex(-3, 1)};
	
		Matrix<Complex> _result(9, Complex(), 3, 3);
		Matrix<Complex> _add(add, 3, 3);
		Matrix<Complex> _sub(sub, 3, 3);
		Complex _scl(2, 0);
		
		std::cout << "default:" << std::endl;
		std::cout << " - shape: (" << _result.get_shape().first << ", " << _result.get_shape().second << ")" << std::endl;
		std::cout << " - value:\n" << _result << std::endl;
		std::cout << std::endl;
	
		_result.add(_add);
		std::cout << "add():\n" << _result << "\n" << std::endl;
		_result.sub(_sub);
		std::cout << "sub():\n" << _result << "\n" << std::endl;
		_result.scl(_scl);
		std::cout << "scl(2):\n" << _result << std::endl;
		Vector<Complex> reshaped = _result.reshape();
		std::cout << "reshape():\n" << reshaped << std::endl;

		std::cout << "\n" << _result << "\n-\n" << _result.row_echelon() << "\n-\n" << _result.rank() << "\n-\n" << _result.inverse() << "\n----\n" << std::endl;
	
		std::cout << "\nTry catch blocks:" << std::endl;
	
		try
		{
			std::cout << _result[{2, 2}] << std::endl;
			std::cout << _result[{2, 3}] << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	
		try
		{
			Matrix<Complex> _error(9, Complex(), 4, 3);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
