#include <iomatfile.hpp>

iomat::iomat() : pmat_(nullptr) {}

iomat::iomat(MATFile *pmat) : pmat_(pmat) {}

iomat::iomat(const std::string& matFile,
			 const std::string& mode) {
	pmat_ = matOpen(matFile.c_str(),mode.c_str());
}

iomat::iomat(const iomat& iomf) : pmat_(iomf.pmat_) {}

iomat::~iomat() {
	if(!empty()) {
		close();
	}
}

int iomat::open(const std::string& matFile) {
	if(mode_.empty()) 
		throw std::runtime_error("MAT-File open mode is unknown.");
	pmat_ = matOpen(matFile.c_str(),mode_.c_str());
	if(pmat_==NULL)
		return -1;
	return 0;
}

int iomat::close() {
	return matClose(pmat_);
}

mxArray *iomat::getVariable(const std::string& var) const {
	return matGetVariable(pmat_,var.c_str());
}

mxArray *iomat::getVariableInfo(const std::string& var) const {
	return matGetVariableInfo(pmat_,var.c_str());
}

mxArray *iomat::getNextVariable(std::string& var) const {
	char** varName;
	mxArray *ret = matGetNextVariable(pmat_,varName);
	var.clear();
	var=std::string(*varName);
	return ret;
}

mxArray *iomat::getNextVariableInfo(std::string& var) const {
	char** varName;
	mxArray *ret = matGetNextVariableInfo(pmat_,varName);
	var.clear();
	var=std::string(*varName);
	return ret;
}

int iomat::putVariable(const std::string& var, const mxArray *value) {
	return matPutVariable(pmat_,var.c_str(),value);
}

int iomat::putvariableAsGlobal(const std::string& var, const mxArray *value) {
	return matPutVariableAsGlobal(pmat_,var.c_str(),value);
}

int iomat::deleteVariable(const std::string& var) {
	return matDeleteVariable(pmat_,var.c_str());
}

std::vector<std::string> iomat::getVariableNames() {
	int *num;
	char** namesChar = matGetDir(pmat_,num);
	std::vector<std::string> varNames;
	std::string name;
	varNames.clear();
	for(int i = 0; i < *num; i++) {
		name.clear();
		name = std::string(namesChar[i]);
		varNames.push_back(name);
	}
	return varNames;
}
