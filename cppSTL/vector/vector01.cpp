
#include <iostream>
#include <vector>


class Cat {

public:
    explicit Cat(int age) : mAge{ age } {}
    void speak() const {
        std::cout << "!" << mAge;
    }
private:
    int mAge;
};

int main()
{
    // 기존 선언방식
    int* numsPtr = new int[5];
    for (int i = 0; i < 5; i++) {
        numsPtr[i] = i;

    }

    delete numsPtr;

    std::vector<int> nums[5];
    /*
    for (int i = 0; i < 5; i++) {
        nums[i] = i;
    }*/
    std::vector<int> nums{ 0,1,2,3,4 };
    std::cout << nums->size() << std::endl; // 4

    nums->emplace_back(5);
    std::cout << nums->size() << std::endl; //5 출력
    nums->pop_back();


    // 이레이터

    for (const int& num : nums)
    {
        std::cout << num << std::endl;
    }

    {
        std::vector<Cat> cats;
        cats.emplace_back(Cat(1));
        cats.emplace_back(Cat(2));
        cats.emplace_back(Cat(3));
        cats.emplace_back(Cat(4));

        for (const auto & cat : cats)
        {
            cat.speak();
        }

    }
}
