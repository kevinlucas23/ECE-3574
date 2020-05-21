/*Name: Kevin
 *Description: This is a code takes notes and store them into a list.
 */

#include <fstream>
#include<string>
#include<cstdlib>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include <algorithm>
#include <functional>

//This keeps track of the priority and the task you want to store on the list.
struct MyStruct
{
	int priority;
	std::string task;
};

//This helps my struct to compare integers which one is greater.
bool operator<(const MyStruct& lhs, const MyStruct& rhs)
{
	return lhs.priority < rhs.priority;
}

//This class helps for reading and writing into the list.
class MyClass
{
public:
	MyClass();
	~MyClass();
	void lireLa(const std::string woufwouf);//Reads the list.
	void ajouterCh(const std::string& tortue, const std::string& genial, const std::string& calecon);//Add all the priority and task into my variables.
	void ecrireDans(const std::string cow, std::size_t position);//Writes into the list.

private:
	std::vector<MyStruct> positiveTask;//It stores all the task that hasn't been check off the list.
	std::vector<MyStruct> negativeTask;//It stores all the task that has been check from the list.
};

MyClass::MyClass()
{
	//Allocate enough memory for my variables.
	positiveTask.reserve(100);
	negativeTask.reserve(100);
}

MyClass::~MyClass()
{
}

void MyClass::lireLa(const std::string woufwouf)
{
	std::ifstream file(woufwouf);//Reads in the path.
	std::string Dragon, Wolf, Tiger;

	if (file.is_open())//Checks if the file can be open.
	{
		file.ignore(200, '[');
		std::getline(file, Dragon, ']');//Checks if it was mark by an x.
		file.ignore(200, '[');
		std::getline(file, Wolf, ']');//Stores the priority.
		file.ignore(1);
		std::getline(file, Tiger);//Takes in the task.
		while (file)//While not at the end of the file
		{
			if (Dragon == " ")//It wasn't done on the list.
			{
				ajouterCh(Wolf, Tiger, "0");
			}
			else if (Dragon == "x")//If it was done.
			{
				ajouterCh("11", Wolf, Tiger);
			}
			file.ignore(200, '[');
			std::getline(file, Dragon, ']');//Checks if it was mark by an X.
			file.ignore(200, '[');
			std::getline(file, Wolf, ']');//Stores the priority.
			file.ignore(1);
			std::getline(file, Tiger);//Takes in the task.
		}//End of while loop.
		file.close();//Closes the file.
	}//End of if loop.
}

void MyClass::ajouterCh(const std::string& tortue, const std::string& genial, const std::string& calecon)
{
	MyStruct goodBye;
	if (std::stoi(tortue) == 11)//If it contains 11 therefore it was mark off from the list.
	{
		goodBye = { std::stoi(genial), calecon };
		negativeTask.push_back(goodBye);//Store all mark off task.
	}
	else if (std::stoi(tortue) < 11 && std::stoi(tortue) > 0)//If it between 1 to 10 then it wasn't mark off.
	{
		goodBye = { std::stoi(tortue), genial };
		positiveTask.push_back(goodBye);//Store all the non-mark off task.
	}
}

void MyClass::ecrireDans(const std::string cow, std::size_t position)
{
	MyStruct bonjour;
	std::stable_sort(positiveTask.begin(), positiveTask.end());//It sorts it from ascending order.
	if (position > 0 && position <= positiveTask.size())//Checks if it is on the list.
	{
		bonjour = positiveTask.at(position - 1);//Stores it at this position.
		positiveTask.erase(positiveTask.begin() + (position - 1));//Erase it from our non-mark list.
		negativeTask.push_back(bonjour);//Stores it in our mark off list.
	}
	else if (position > positiveTask.size() && position <= (positiveTask.size() + negativeTask.size()))//Checks if it's on the list or not?
	{
		std::cout << "Sorry you can't remove because it's already check off your list" << std::endl;
	}

	std::ofstream fole(cow);//Reads in the path.
	int numero = 1;
	if (fole.is_open())//Checks if it can opent the file.
	{
		//Write everything on to list as describe.
		for (std::size_t i = 0; i < positiveTask.size(); i++)
		{
			fole << std::to_string(numero) << ":" << "[ ]" << "[" << positiveTask.at(i).priority << "] " << positiveTask.at(i).task << std::endl;
			numero++;
		}
		for (std::size_t i = 0; i < negativeTask.size(); i++)
		{
			fole << std::to_string(numero) << ":" << "[x]" << "[" << negativeTask.at(i).priority << "] " << negativeTask.at(i).task << std::endl;
			numero++;
		}
		fole.close();//CLoses the file.
	}//End of if.
}

int main(int argc, char* argv[])
{
	std::string a, test, hiho;
	std::ifstream file;
	std::ofstream ofile;
	std::vector<std::string> lines, cmdk;
	int counter;
	counter = 0;
	MyClass letsGo;
	a = "./note.txt";

	//Input all the commands into the vector.
	for (int i = 1; i < argc; i++)
	{
		cmdk.push_back(std::string(argv[i]));
	}

	if (cmdk.empty())//If no arguments were inputted.
	{
		std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
		return EXIT_FAILURE;
	}
	//checks for the 1st input command.
	if (cmdk.at(0) == "-f")
	{
		//checks if there are sufficient arguments passed.
		if (cmdk.size() < 3)
		{
			std::cout << "Insufficient input commands, check again" << std::endl;
			return EXIT_FAILURE;
		}
		else
		{
			letsGo.lireLa(cmdk.at(1));//Reads the list file.
			if (cmdk.at(2) == "list")
			{
				file.open(cmdk.at(1));
				//checks if the file can be open
				if (file.fail())
				{
					std::cout << "sorry, the file can't be open, try again" << std::endl;
					return EXIT_FAILURE;
				}
				//reads all the line from the file and stores them in a vector
				while (file.peek() != EOF)
				{
					std::getline(file, test);
					lines.push_back(test);
				}
				//prints out all the list
				for (std::size_t i = 0; i < lines.size(); i++)
				{
					std::cout << lines[i] << std::endl;
				}
				file.close();
				return EXIT_SUCCESS;
			}
			else if (cmdk.at(2) == "add")
			{
				if (cmdk.size() < 4)
				{
					std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
					return EXIT_FAILURE;
				}
				//copy all the task from the list
				test = cmdk.at(3);
				for (std::size_t b = 4; b < cmdk.size(); b++)
				{
					test = test + " " + cmdk.at(b);
				}
				//writes it to our list
				letsGo.ajouterCh("5", test, "0");
				letsGo.ecrireDans(cmdk.at(1), 0);//Writes into the list file.
			}
			else if (cmdk.at(2) == "-p")//checks if it is a priority or not
			{
				if (cmdk.size() < 5)
				{
					std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
					return EXIT_FAILURE;
				}
				if (cmdk.at(4) == "add")
				{
					if (cmdk.size() < 6)
					{
						std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
						return EXIT_FAILURE;
					}
					//copy all the task from the list
					test = cmdk.at(5);
					for (std::size_t b = 6; b < cmdk.size(); b++)
					{
						test = test + " " + cmdk.at(b);
					}
					//writes it to our list.
					for (int i = 0; i < cmdk.at(3).length(); i++)//check if it is a digit or not.
					{
						if (isdigit(cmdk.at(3)[i]) == false)
						{
							std::cout << "Sorry the priority is not a digit" << std::endl;
							return EXIT_FAILURE;
						}
						else
						{
							if (std::stoi(cmdk.at(3)) > 10 || std::stoi(cmdk.at(3)) < 1)
							{
								std::cout << "Sorry it's out of bounce" << std::endl;
								return EXIT_FAILURE;
							}
							letsGo.ajouterCh(cmdk.at(3), test, "0");
							letsGo.ecrireDans(cmdk.at(1), 0);//Writes into the list file.
						}
					}
				}
			}//without a priority
			else if (cmdk.at(2) == "mark")//takes it from our list
			{
				file.open(cmdk.at(1));
				//checks if the file can be open
				if (file.fail())
				{
					std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
					return EXIT_FAILURE;
				}
				while (std::getline(file, hiho))
				{
					counter++;//counts how many items are on the list.
				}
				if (counter < std::stoi(cmdk.at(3)))
				{
					std::cout << "That position doesn't exit on your list" << std::endl;
					return EXIT_FAILURE;
				}
				file.close();
				letsGo.ecrireDans(cmdk.at(1), std::stoi(cmdk.at(3)));//Writes into the list file.
			}
			else
			{
			std::cout<<"Wrong input arguement check again"<<std::endl;
			return EXIT_FAILURE;
			}
		}
	}
	else
	{
		letsGo.lireLa(a);//Reads the list file.
		if (cmdk.at(0) == "add")
		{
			if (cmdk.size() < 2)
			{
				std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
				return EXIT_FAILURE;
			}
			//copy all the task from the list
			test = cmdk.at(1);
			for (std::size_t b = 2; b < cmdk.size(); b++)
			{
				test = test + " " + cmdk.at(b);
			}
			//writes it to our list
			letsGo.ajouterCh("5", test, "0");
			letsGo.ecrireDans(a, 0);//Writes into the list file.
		}
		else if (cmdk.at(0) == "-p")//checks if it is a priority or not
		{

			if (cmdk.size() < 3)
			{
				std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
				return EXIT_FAILURE;
			}
			if (cmdk.at(2) == "add")
			{
				//copy all the task from the list
				if (cmdk.size() < 4)
				{
					std::cout << "Not sufficient number of arguments passed, please check again or retry later." << std::endl;
					return EXIT_FAILURE;
				}
				test = cmdk.at(3);
				for (std::size_t b = 4; b < cmdk.size(); b++)
				{
					test = test + " " + cmdk.at(b);
				}
				//writes it to our list.
				for (int i = 0; i < cmdk.at(1).length(); i++)//check if it is a digit or not.
				{
					if (isdigit(cmdk.at(1)[i]) == false)
					{
						std::cout << "Sorry the priority is not a digit" << std::endl;
						return EXIT_FAILURE;
					}
					else
					{
						if (std::stoi(cmdk.at(1)) > 10 || std::stoi(cmdk.at(1)) < 1)
						{
							std::cout << "Sorry it's out of bounce" << std::endl;
							return EXIT_FAILURE;
						}
						letsGo.ajouterCh(cmdk.at(1), test, "0");
						letsGo.ecrireDans(a, 0);//Writes into the list file.
					}
				}
			}
		}

		else if (cmdk.at(0) == "list")
		{
			file.open(a);
			if (file.fail())
			{
				std::cout << "Sorry, that file doesn't exist" << std::endl;
				return EXIT_FAILURE;
			}
			//reads all the line from the file and stores them in a vector
			while (file.peek() != EOF)
			{
				std::getline(file, test);
				lines.push_back(test);
			}
			//prints out the list
			for (std::size_t i = 0; i < lines.size(); i++)
			{
				std::cout << lines[i] << std::endl;
			}
			file.close();
		}

		else if (cmdk.at(0) == "mark")
		{
			file.open(a);
			//checks if the file can be open
			if (file.fail())
			{
				return EXIT_FAILURE;
			}
			while (std::getline(file, hiho))
			{
				counter++;
			}
			if (counter < std::stoi(cmdk.at(1)))
			{
				std::cout << "That position doesn't exit on your list" << std::endl;
				return EXIT_FAILURE;
			}
			file.close();
			letsGo.ecrireDans(a, std::stoi(cmdk.at(1)));//Writes into the list file.
		} 
		else
		{
			std::cout << "Wrong input arguments" << std::endl;
			return EXIT_FAILURE;
		}
	}//End of if.
	return 0;
}
