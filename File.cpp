#include "File.hpp"
      
std::string File::getName() const {
   return filename_;
}

std::string File::getContents() const {
   return contents_;
}

void File::setContents(const std::string& new_contents) {
   contents_ = new_contents;
}

int* File::getIcon() const {
   return icon_;
}

void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a; 
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================
/**
      * @brief Constructs a new File object.
      * 
      * @param filename A const reference to a string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
      *    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
      *    - If no extension is provided (e.g. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
      *    - Default value of "NewFile.txt" if none provided or if filename is empty 
      * @param contents A string representing the contents of the file. Default to empty string if none provided.
      * @param icon A pointer to an integer array with length ICON_DIM. Default to nullptr if none provided.
      * @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
      * @note You'll notice we provide a default value for the first possible argument (filename)
      *       Yes, this means we can define override the default constructor and define a parameterized one simultaneously.
      */
      File::File(const std::string& filename, const std::string& contents, int* icon) : filename_("NewFile.txt"), contents_(contents), icon_(icon) {
         if(!filename.empty()){
            int period_count = 0;
            for(const char& c : filename) {
               if(!std::isalnum(c) && c != '.') 
                  throw InvalidFormatException("Invalid filename: " + filename);
               if(c == '.') period_count++;
            }
            if(period_count == 0) {
               filename_ = filename + ".txt"; 
            } else if(period_count == 1) {
               filename_ = filename; 
            } else {
               throw InvalidFormatException("Invalid.");
            }
         }
   }
     
      /**
      * @brief Calculates and returns the size of the File Object (IN BYTES), using .size()
      * @return size_t The number of bytes the File's contents consumes
      * @note Consider this: how does this relate to the string's length? Why is that the case?
      */
      size_t File::getSize() const{
         return contents_.size();
      }

      /**
       * @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
       * @param rhs A const reference to the file to be copied from
       */
      File::File(const File &rhs) : filename_(rhs.filename_), contents_(rhs.contents_), icon_(nullptr) {
         if(rhs.icon_ != nullptr) {
            icon_ = new int[ICON_DIM]; 
            std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
         }
      } 

      /**
       * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File.
       * 
       * @param rhs A const reference to the File object to be copied
       * @return A reference to the new File copy
       * @note If copy assignment operator is invoked upon itself, do nothing.
       */
      File& File::operator=(const File& rhs){
      //Sefl assignment check
      if(this != &rhs) {
         filename_ = rhs.filename_;
         contents_ = rhs.contents_;
         delete[] icon_;
         if(rhs.icon_ != nullptr) {
            icon_ = new int[ICON_DIM]; 
            std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
         } else {
            icon_ = nullptr;
         }
      }
      return *this;
   }

      /**
       * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
       * @param rhs The File whose data is moved
       * @post The rhs File object is left in a valid, but ready to be deleted state:
       *    - All string members are themselves moved.
       *    - ALl pointers are set to nullptr
       */
      File::File(File&& rhs) noexcept {
         filename_ = std::move(rhs.filename_);
         contents_ = std::move(rhs.contents_);
         icon_ = rhs.icon_;
         rhs.icon_ = nullptr;
      }
      /**
       * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
       * 
       * @param rhs The File whose data is moved
       * @return A reference to the object which the data was moved into
       * @post The rhs File object is left in a valid, but ready to be deleted state:
       *    - All string members are moved.
       *    - ALl pointers are set to nullptr
       * @note If move assignment operator is invoked upon itself, do nothing.
       */
      File& File::operator=(File&& rhs)noexcept{
         //Check for self assignment, do nothing. 
         if(this != &rhs){
            delete[] icon_;
            filename_ = std::move(rhs.filename_);
            contents_ = std::move(rhs.contents_);
            icon_ = std::move(rhs.icon_);
            rhs.icon_ = nullptr;
         }
         return *this;
      }

      /**
       * @brief (DESTRUCTOR) Routine for object deletion
       * @post All dynamically allocated memory is released
       */
      File::~File(){
         delete[] icon_;
      } 