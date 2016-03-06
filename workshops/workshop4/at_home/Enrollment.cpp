



bool Enrollment::isValid()const{
  return name_ && name_[0];
}

void Enrollment::setEmpty(){
  name_[0] = 0;
  code_[0] = 0;
  year_ = 0;
  semester_ = 0;
  slot_ = 0;
  enrolled_ = false;
}

bool Enrollment::isEnrolled() const{
  return enrolled_;
}


void Enrollment::display(bool nameOnly)const{
  if (isValid()){
    cout << name_;
    if (!nameOnly){
      cout << endl << code_ << ", Year: " << year_ << " semester: " << semester_ << " Slot: " << slot_ << endl;
      cout << "Status: " << (isEnrolled() ? "E" : "Not e") << "nrolled." << endl;
    }
  }
  else{
    cout << "Invalid enrollment!" << endl;
  }
}

