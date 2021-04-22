#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>
#include <iterator>
#include <cmath>
#include <stack>
#include <queue>
#include <map>

////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(const std::list<float>& values)
{
	std::pair<float, float> result(0.f, 0.f);
	float sum = 0;
	float mean = 0;
	float n = values.size();
	float sd = 0;
	float numerator = 0;
	float temp = 0;

	for(std::list<float>::const_iterator iterator = values.begin(), end = values.end();
	iterator != end; ++iterator) {
		sum += *iterator;
	}

	mean = sum/n;

	result.first = mean;

	for(std::list<float>::const_iterator iterator = values.begin(), end = values.end();
	iterator != end; ++iterator) {
		temp = *iterator-mean;
		numerator += temp*temp;
	}

	sd = sqrt(numerator/n);

	result.second = sd;
	
	return result;
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor {
public:
	float visitTree(const Tree& tree, bool countOnlyEvenLevels){ 
		float sum = 0.0;
		sum += tree.value;
		if(!countOnlyEvenLevels){
			for(Tree tree : tree.children){
				sum += visitTree(tree, countOnlyEvenLevels);
			}
		}else{
			return evenLevel(tree, 0);
		}
		return sum;
	}

	float evenLevel(const Tree& tree, int level){	
		float sum = 0.0;
		if(level % 2 == 0){
			sum += tree.value;
		}
		for(Tree tree : tree.children){
			sum += evenLevel(tree, level + 1);
		}
		return sum;
	}
	
};
	
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {
public:

	Complex(float real, float imaginary) : real(real), im(imaginary){};

	float real, im;

};

	Complex operator + (Complex c1, Complex c2){
		float sumReal = c1.real + c2.real;
		float sumIm = c1.im + c2.im;
		return Complex(sumReal, sumIm);
	};

	Complex operator - (Complex c1, Complex c2){
		float sumReal = c1.real - c2.real;
		float sumIm = c1.im - c2.im;
		return Complex(sumReal, sumIm);
	};

	Complex operator * (Complex c1, Complex c2){
		float c1Real = c1.real;
		float c1Im = c1.im;
		float c2Real = c2.real;
		float c2Im = c2.im;

		float resultReal = c1Real*c2Real + (-1)*c1Im*c2Im;
		float resultIm = c1Im*c2Real + c2Im*c1Real;

		return Complex(resultReal, resultIm);
	};



//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::list<float> heights)
{    
	float max = heights.front();
	float max2 = heights.back();
	float limit = 0;
	float currentH = 0;
	float result = 0;
	float diff = 0;
	float diff2 = 0;
	float result2 = 0;
	float final = 0;
	float limitIndex = 0;
	float currentIndex = heights.size() - 1;
	float h = heights.size() - 1;

	for(std::list<float>::const_iterator iterator = heights.begin(), end = heights.end();
		iterator != end; ++iterator) {
			if(*iterator > limit) {
				limit = *iterator;
			}
		}

	for(std::list<float>::const_iterator iterator = heights.begin(), end = heights.end();
		iterator != end; ++iterator) {
			if(*iterator == limit) {
				break;
			}
			++limitIndex;
		}
	
	//Loops until the tallest
	for(std::list<float>::const_iterator iterator = heights.begin(), end = heights.end();
		iterator != end; ++iterator) {
			if(*iterator < max && max < limit){
					diff = max - *iterator;
					result += diff;
					heights.pop_front();
					}else if(*iterator > max) {
						max = *iterator;
					heights.pop_front();
				}

		}
	
	for(std::list<float>::reverse_iterator rit = heights.rbegin(); rit != heights.rend();
		++rit) {
		if(currentIndex > limitIndex){
			if(*rit < max2){
				diff2 = max2 - *rit;
				result2 += diff2;
			} else if(*rit > max2){
				max2 = *rit;
			} 
		} else if (*rit == limit){
				break;
			}
			currentIndex = currentIndex - 1;
	}

		final = result + result2;

		return final;
}

//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
typedef std::pair<int, int> location;


int Labyrinth(std::set<std::pair<location, location> > labyrinth, int size)
{
	std::queue<location> queue;
	std::stack<std::pair<location, location> > stack;
    std::pair<location, location> vertex;
	std::set<location> visited;
	std::list<int> list;
	std::map<int, int> validList;
    location curr = location(0,0);
	bool isValid = true;
	int valid = 0;

	queue.push(curr);
	visited.insert(curr);

	int distance = 1;
	int cx;
	int cy; 

	int counter = 0;

	while(!queue.empty()){
		
		curr.first = queue.front().first;
		curr.second = queue.front().second;

		queue.pop();
		int cx = curr.first;
		int cy = curr.second;

		if(cx == size - 1 && cy == size - 1){
			break;
		}

		for(int i = 0; i < 4; i++) {

			int nx;
			int ny;

			switch(i) {
				case 0: ny = cy + 1; //down
						nx = cx;
						break;
				case 1: ny = cy - 1; //up
						nx = cx;
						break;
				case 2: nx = cx - 1; //left
						ny = cy;
						break;
				case 3: nx = cx + 1; //right
						ny = cy;
						break;
				default:
						std::cout << "Something went wrong\n" << std::endl;
						break;
			}

			location newLoc = location(nx, ny);

			isValid = (nx >= 0) && (nx < size) && (ny >= 0) && (ny < size);

			if(i == 0 || i == 3){
				vertex.first = curr;
				vertex.second = newLoc;
			} 
			if(i == 1 ||i == 2){
				vertex.first = newLoc;
				vertex.second = curr;
			}

			if(!labyrinth.count(vertex) && !visited.count(newLoc) && isValid){
				queue.push(newLoc);
				visited.insert(newLoc);
				stack.push(std::make_pair(newLoc, curr));
			}

		}

	}

	//Trace backward to find the shortest path
	location loc = location(size - 1, size - 1);
	while(!stack.empty()){
		if(loc == stack.top().first){
			distance++;
			loc = stack.top().second;
		}
		stack.pop();
		
	}
	// std::cout << distance << std::endl;
	return distance;
}

//////////////////////////////////////////////////////////////////

#endif