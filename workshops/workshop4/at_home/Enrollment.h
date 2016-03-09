


class Enrollment{
private:
  char name_[31];
  char code_[11];
  int year_;
  int semester_;
  int slot_;
  bool enrolled_;
public:


  void display(bool nameOnly = false)const;
  bool isValid()const;
  void setEmpty();
  bool isEnrolled() const;

};

