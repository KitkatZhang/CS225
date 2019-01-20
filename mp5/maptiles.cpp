/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    
    vector<Point<3>> tile;
    map<Point<3>, int> index;

    for (size_t i=0; i < theTiles.size(); i++){
      Point<3> pixel_ave = convertToXYZ(theTiles[i].getAverageColor());
      tile.push_back(pixel_ave);
    }
   
    for (size_t i =0; i< theTiles.size();i++){
      index[tile[i]]=i;
    }

    KDTree<3> tiletree(tile);

    for (int row=0;row<theSource.getRows();row++){
      for(int col=0;col<theSource.getColumns();col++){
        Point<3> target = convertToXYZ(theSource.getRegionColor(row,col));
        Point<3> key = tiletree.findNearestNeighbor(target);
        int idx = index[key];
        result->setTile(row,col,&theTiles[idx]);
      }
    }
    
    return result;           
}

