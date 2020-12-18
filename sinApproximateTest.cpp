// sinApproximateTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//dfd

#include <iostream>
#include <time.h>
#include <math.h>

constexpr auto doubleTwoPI = 6.28318530718;
constexpr auto doublePI =    3.14159265359;
constexpr auto doubleHalfPI = 1.57079632679;
constexpr auto  a1Double = -0.467;
constexpr auto  a2Double = -0.4846785;
constexpr auto epsillon = 0.00001;


double getSin(const double x) {
	
	if (x < 0)
		return -getSin(x);
	if (x <= 0.236872109056403)
		return x;
	if (x > doubleTwoPI)                           //ask JVM to do modulus with double : no problem! :D
		return getSin(std::fmod(x, doubleTwoPI));  //ask C++ compiler to do modulus with double : F you I refuse to calculate &$^%&#$%@$&
	if (x > doublePI)
		return (-1) * getSin(x - doublePI);
	if (x > doubleHalfPI)
		return getSin(doublePI - x);
		
	if (x < 0.591385707016756)
		return -0.1 * x * (x - doublePI) * (x + doublePI);
	if (x < 0.801774927340932)
		return a1Double * ((x - doubleHalfPI) * (x - doubleHalfPI)) + 1;
		
	return a2Double * ((x - doubleHalfPI) * (x - doubleHalfPI)) + 1;

}

double getTaylorSin(const double x) {

	if (x < 0)
		return -getTaylorSin(x);
	if (x > doubleTwoPI)                           //ask JVM to do modulus with double : no problem! :D
		return getTaylorSin(std::fmod(x, doubleTwoPI));  //ask C++ compiler to do modulus with double : F you I refuse to calculate &$^%&#$%@$&
	if (x > doublePI)
		return (-1) * getSin(x - doublePI);
	if (x > doubleHalfPI)
		return getTaylorSin(doublePI - x);

	int sign = -1;
	double divisor = 1;
	int i = 1;
	double num = 0;
	double dividend = x;
	double result = dividend;

	do {

		dividend = dividend * x * x * sign;

		i += 1;
		divisor *= i;
		i += 1;
		divisor *= i;

		num = dividend / divisor;

		result += num;

	} while (abs(num) > 0.0);

	return result;

}

void testTime()
{
	
	const double testTo = doubleHalfPI;

	clock_t start, end;
	double result;

	start = clock();

	for (double i = 0.0; i < testTo; i += epsillon)
	{
		getSin(i);
	}

	end = clock();
	result = (double) (end - start);
	std::cout << "result : " << result << " ms in approx" << std::endl;


	start = clock();

	for (double i = 0.0; i < testTo; i += epsillon)
	{
		getTaylorSin(i);
	}

	end = clock();
	result = (double)(end - start);
	std::cout << "result : " << result << " ms in Taylor" << std::endl;

}


void testErr()
{

	double e, x, max = 0.0;
	const double testTo = doubleHalfPI;

	for (double i = 0.0; i < testTo; i += epsillon)
	{
		e = fabs( 1 - (getTaylorSin(i) / sin(i)) );
		//max = (e > max) ? e : max;
		if (e > max) { max = e; x = i; }
	}

	std::cout << max << " in " << x << std::endl; //in Taylor, result is 6.66134e-16 in 0.61244
	                                              //in approx, result is 0.00982811  in 2.55021
}



int main()
{

	testErr();
	return 0;

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
