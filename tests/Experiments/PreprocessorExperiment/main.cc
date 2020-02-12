#define WRAP_ALL_TYPES(PREFIX, SUFFIX) \
    PREFIX short int SUFFIX \
    PREFIX unsigned short int SUFFIX \
    PREFIX int SUFFIX \
    PREFIX unsigned int SUFFIX \
    PREFIX long int SUFFIX \
    PREFIX unsigned long int SUFFIX \
    PREFIX long long int SUFFIX \
    PREFIX unsigned long long int SUFFIX \
    PREFIX signed char SUFFIX \
    PREFIX unsigned char SUFFIX \
    PREFIX char SUFFIX \
    PREFIX float SUFFIX \
    PREFIX double SUFFIX \
    PREFIX long double SUFFIX \

#define INSTANTIATE_CLASS_TEMPLATES(T) \
    WRAP_ALL_TYPES(template class T<, >;)\

template<typename T>
class TestClass {

};

template<typename T>
void testFunction(){

}

INSTANTIATE_CLASS_TEMPLATES(TestClass)
INSTANTIATE_FUNCTION_TEMPLATES(testFunction)

int main(){
    TestClass<int> a;
    testFunction<float>(3);
}
