#include "global.hpp"
#include "walle_matrix.hpp"
#include "printing.hpp"

using boost::numeric::ublas::matrix;

namespace global {


	float minimize(Robot robot, Map const& map) {
		int size = map.getSize();
		WallE_Matrix directionMat(size);
		matrix<int> costMat(size, size);

		directionMat(0,0) = 2;
		costMat(0,0) = 0;

		for(int row = 1 ; row < size ; ++row) {
			directionMat(0, row) = EAST;
			costMat(0, row) = costMat(0, row - 1) + map.northCost(0, row - 1);
		}

		for(int col = 1 ; col < size ; ++col) {
			directionMat(col, 0) = NORTH;
			costMat(col, 0) = costMat(col - 1, 0) + map.eastCost(col - 1, 0);
		}

		for(int row = 1 ; row < size ; ++row) {
			for(int col = 1 ; col < size ; ++col) {

				float northCost = map.northCost(col, row-1) + costMat(col, row-1),
				      eastCost  = map.eastCost(col-1, row) + costMat(col-1, row),
				      northEastCost = map.northEastCost(col-1, row-1) + costMat(col-1, row-1);

				if(northCost < eastCost) {
					if(northCost < northEastCost) {
						directionMat(col, row) = NORTH;
						costMat(col, row) = northCost;
					} else {
						directionMat(col, row) = NORTH_EAST;
						costMat(col, row) = northEastCost;
					}
				} else if(eastCost < northEastCost) {
					directionMat(col, row) = EAST;
					costMat(col, row) = eastCost;
				} else {
					directionMat(col, row) = NORTH_EAST;
					costMat(col, row) = northEastCost;
				}
			}
		}

		std::cout << directionMat << std::endl;
		std::cout << costMat      << std::endl;

		std::vector<int> reversed_directions;
		// Parcours de la matrice dans la méthode WallE_Matrix::iterator::operator++
		for(int direction : directionMat) {
			reversed_directions.push_back(direction);
		}

		std::cout << map << robot;
		for(auto it = reversed_directions.rbegin() ; it != reversed_directions.rend() ; ++it) {
			if(*it == NORTH) {
				robot.goNorth();
				std::cout << robot;
			} else if(*it == EAST) {
				robot.goEast();
				std::cout << robot;
			} else {
				robot.goNorthEast();
				std::cout << robot;
			}
		}

		return robot.getTotalCost();
	}
}