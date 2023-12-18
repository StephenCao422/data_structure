/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

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
    //KDTree construction
    vector<Point<3>> avgTileColors;
    map<Point<3>, TileImage*> avgColorToTileMap;

    for (TileImage &tile : theTiles) {
        LUVAPixel avgColor = tile.getAverageColor();
        Point<3> avgColorPoint = convertToXYZ(avgColor);
        avgTileColors.push_back(avgColorPoint);
        avgColorToTileMap[avgColorPoint] = &tile;
    }
    KDTree<3> colorTree(avgTileColors);
    //create MosaicCanvas
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(rows, cols);

    //tile matching & mosaic creation
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            LUVAPixel regionColor = theSource.getRegionColor(y, x);
            Point<3> regionColorPoint = convertToXYZ(regionColor);
            Point<3> nearestColorPoint = colorTree.findNearestNeighbor(regionColorPoint);
            TileImage* matchingTile = avgColorToTileMap[nearestColorPoint];
            mosaic->setTile(y, x, matchingTile);
        }
    }

    return mosaic;
}

