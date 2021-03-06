#ifndef __TISSUECELL_H_DEFINED__
#define __TISSUECELL_H_DEFINED__

// tissuecell.h
//================================================
// Defines the TissueCell namespace.
// In this namespace, we define typedefs for a single cell (Unit) and a vector of cells (Collection).
#ifdef DP
#define MACRO_PRECISION double
#else
#define MACRO_PRECISION float
#endif

#include <iostream>
#include <vector>
#include "MersenneTwister.h"


namespace TissueCell{
	// Create the data struct with either a float or a double to vary precision
	typedef MACRO_PRECISION RealType;

	struct CellData
	{
		RealType angle;
		RealType x;
		RealType y;
		RealType Fx;
		RealType Fy;
	
		CellData(RealType mx, RealType my, RealType ma): x(mx), y(my), angle(ma) {};
		CellData(): x(0), y(0), angle(0) {};

		static CellData Create_xya(RealType mx, RealType my, RealType ma){
			return CellData(mx,my,ma);}

		static CellData CreateRandom(MTRand& rng){
			return CellData(rng.rand(), rng.rand(), rng.rand());}

		void TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng);
	};

	typedef CellData Unit;
	typedef std::vector<Unit> Vector;

	/// Create a mutual interaction, where each cell moves relative to the other. Because forces are additive
	///  Interaction range is (-box_size/2, box_size/2] (open on bottom, closed on top).
	///  All particles must begin inside of the box.
	///  Throws an invalid_argument exception if Rcut <= Req
	void Interact(Unit& cell1, Unit& cell2, RealType r_cut, RealType r_eq, RealType box_size, RealType F_adh, RealType F_rep);


}


#endif 
