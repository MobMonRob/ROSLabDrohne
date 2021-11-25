


template <typename DataType>
class Optional
{
public:
	Optional(DataType Data = DataType(), bool Valid = false);

	void setData(DataType Data) { this->Data_ = Data; };
	void setValid(bool Valid) { this->isValid_ = Valid; };

	DataType getData() { return this->Data_; };
	bool getValid() { return this->isValid_; };

private:
	DataType Data_;
	bool isValid_;
};

