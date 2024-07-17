# SingletonTemplate
A simple singleton template to inherit from in order to make a class a singleton

## Usage ##

* `Singleton.h` contains the actual singelton template
* `Test.[h,cpp]` contain an example class inheriting from Singleton.h

Included is a test program that demonstrates how it behaves, it is written in a way that keeps all `std::shared_ptr` and `std::weak_ptr` valid, even if the instance gets resetted. Copy, assign and move protection is automatically included.