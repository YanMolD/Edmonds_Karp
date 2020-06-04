#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include "C:\Users\yan\source\repos\4sem_kurs\reading.h"
#include "C:\Users\yan\source\repos\4sem_kurs\Ed_K_alg.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KURSUT
{
	TEST_CLASS(KURSUT)
	{
	public:

		TEST_METHOD(Test_exception_no_source)
		{
			ofstream input_file_example("Text_input.txt");
			input_file_example.clear();
			input_file_example << "N;V;5\nN;I;3\nV;I;2\nV;G;3\nI;F;2\nG;F;4\nF;T;5\nG;T;2\nI;K;1\nK;F;1";
			input_file_example.close();
			ifstream input_file("Text_input.txt");
			try
			{
				read_file(input_file);
			}
			catch (invalid_argument exception)
			{
				Assert::AreEqual(exception.what(), "In this net doesn't exist source");
			}
		}
		TEST_METHOD(Test_exception_no_sink)
		{
			ofstream input_file_example("Text_input.txt");
			input_file_example.clear();
			input_file_example << "S;V;5\nS;I;3\nV;I;2\nV;G;3\nI;F;2\nG;F;4\nF;R;5\nG;R;2\nI;K;1\nK;F;1";
			input_file_example.close();
			ifstream input_file("Text_input.txt");
			try
			{
				read_file(input_file);
			}
			catch (invalid_argument exception)
			{
				Assert::AreEqual(exception.what(), "In this net doesn't exist sink");
			}
		}
		TEST_METHOD(Test_exception_empty_file)
		{
			ofstream input_file_example("Text_input.txt");
			input_file_example.clear();
			input_file_example.close();
			ifstream input_file("Text_input.txt");
			try
			{
				read_file(input_file);
			}
			catch (out_of_range exception)
			{
				Assert::AreEqual(exception.what(), "No symbols in file");
			}
		}
		TEST_METHOD(Test_exception_no_ways)
		{
			ofstream input_file_example("Text_input.txt");
			input_file_example.clear();
			input_file_example << "S;O;3\nS;P;3\nO;P;2\nQ;R;4\nR;T;2\nQ;T;3";
			input_file_example.close();
			ifstream input_file("Text_input.txt");
			try
			{
				read_file(input_file);
			}
			catch (invalid_argument exception)
			{
				Assert::AreEqual(exception.what(), "In this net doesn't exist way from source to sink");
			}
		}
		TEST_METHOD(Test_exception_negative_data)
		{
			ofstream input_file_example("Text_input.txt");
			input_file_example.clear();
			input_file_example << "S;V;-5\nS;I;-3\nV;I;-2\nF;T;5\nG;T;2\nI;K;1";
			input_file_example.close();
			ifstream input_file("Text_input.txt");
			try
			{
				read_file(input_file);
			}
			catch (invalid_argument exception)
			{
				Assert::AreEqual(exception.what(), "Incorrect data in file");
			}
		}
		TEST_METHOD(Test_exception_loop)
		{
			ofstream input_file_example("Text_input.txt");
			input_file_example.clear();
			input_file_example << "S;V;5\nS;I;3\nV;I;2\nV;G;3\nI;F;2\nG;F;4\nF;T;5\nG;T;2\nI;K;1\nK;F;1\nK;I;1";
			input_file_example.close();
			ifstream input_file("Text_input.txt");
			try
			{
				read_file(input_file);
			}
			catch (invalid_argument exception)
			{
				Assert::AreEqual(exception.what(), "In this net exist a loop");
			}
		}
	};
}