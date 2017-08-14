#ifndef iomatfile_hpp
#define iomatfile_hpp

#include "mat.h"
#include <string>
#include <vector>
#include <fstream>

class iomat {
public:
	//! \name Constructors
	//@{
	// default constructor
	iomat();
	iomat(MATFile *pmat);
	iomat(const std::string& file,
		  const std::string& mode);
	iomat(const iomat& iomf);
	//@}
	//! Destructor
	~iomat();
	//! \name File Open/Cloes
	//@{
	//! open file: return 0 if successful, otherwise -1
	int open(const std::string&);
	//! close file: return 0 if successful, otherwise -1
	int close();
	//@}
	//! \name Getters
	//@{
	mxArray *getVariable(const std::string&) const;
	mxArray *getVariableInfo(const std::string&) const;
	mxArray *getNextVariable(std::string&) const;
	mxArray *getNextVariableInfo(std::string&) const;
	//@}
	//! \name Putters and Modifiers
	//@{
	int putVariable(const std::string&,const mxArray *);
	/*! Puts an mxArray into a MAT-file.
		return 0 if sucessful and nonzero if an error occurs.
	*/
	int putvariableAsGlobal(const std::string&, const mxArray *);
	/*! Delete variable in a MAT-file.
		return 0 if sucessfully delete, and nonzero otherwise.
	*/	
	int deleteVariable(const std::string&);
	//@}
	//! \name Info Inspectors
	//@{
	//! get a list of the names of the mxArrays in the MAT-file.
	std::vector<std::string> getVariableNames();
	//! get MAT-file open mode
	std::string getMode();
	//! check if MAT-file pointer is empty
	bool empty();
	//@}

private:
	MATFile *pmat_;
	std::string mode_;
};

// inline definitions
inline std::string iomat::getMode() {
	return mode_;
}

inline bool iomat::empty() {
	return pmat_ == nullptr;
}
#endif
