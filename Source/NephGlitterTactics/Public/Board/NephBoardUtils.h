#pragma once

UENUM()
enum class ENephDirections : uint8
{
	North,
	East,
	South,
	West
};

class NEPHGLITTERTACTICS_API NephBoardUtils
{
public:
	
	static ENephDirections GetDirectionToTile(FIntVector2 Tile1, FIntVector2 Tile2)
	{
		if (Tile1.Y < Tile2.Y)
			return ENephDirections::North;
		if (Tile1.X < Tile2.X)
			return ENephDirections::East;
		if (Tile1.Y > Tile2.Y)
			return ENephDirections::South;
		return ENephDirections::West;
	}
	
	static FVector DirectionToEuler(ENephDirections Direction)
	{
		return FVector(0, static_cast<uint8>(Direction) * 90, 0);
	}
};
