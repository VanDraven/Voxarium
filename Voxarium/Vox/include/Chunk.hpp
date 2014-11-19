#pragma once

#include <iostream>
#include "Octree.hpp"

namespace voxarium{
	class Chunk{

		private :
		int profondeur;
		

		public :
		Octree root;
		
		Chunk();
		void genFlatFloor(Octree &subTree, int &etage);
	};
}
