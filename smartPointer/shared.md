
# shared_ptr

```std::shared_ptr```은 객체의 소유권을 다른 포인터 변수들과 공유할 수 있는 포인터이다. 즉 하나의 특정 객체를 참조하는 포인터가 여러 개 
존재할 수 있다. ```std::unique_ptr```과 달리 복사가 가능하다. 동일한 객체를 가리키는 ```std::shared_ptr```은 참조하는 횟수를 저장하는 참조 횟수(reference count)를 틍해 참조한 횟수를 저장하여 포인터가 복사될 때마다 1씩 증가시키고 해제할 때마다 1씩 감소한다. 포인터가 가리키는 객체의 참조 횟수가 0이 되었을 떼 메모리가 해제된다. 참조 횟수는 ```use_count()``` 멤버 함수를 통해 가져올 수 있다. 

```std::shared_ptr```객체가 복사되어도 메모리 공간을 증가하지 않는다. 

```C++
int main(int argc, char const *argv[])
{
	
	shared_ptr<int> foo(new int(6));
	cout << foo.use_count() << endl;
	auto bar = foo;
	cout << bar.use_count() << endl;
	bar.reset();
	cout << foo.use_count() << endl;
	foo.reset();
	cout << foo.use_count() << endl;

	return 0;
}
```

## 메모리 누수 

![image](https://user-images.githubusercontent.com/54939319/189467680-901278f2-2591-44d0-aa9e-f488d09a663f.png)

![image](https://user-images.githubusercontent.com/54939319/189467665-3f21a670-4ec1-4cca-bd48-0ff105927f0d.png)


- Garbage Collector가 없는 C++는 shared_ptr를 사용한다면 reference counting에 의해서 object 의 life cycle을 결정 , 당연히 ref count가 0 이 되면 object가 해제.

- object를 가르키고 있는 pointer가 0이 되면 object 해제.

- 하지만 cycle이 일어나게 되면 object를 가르키는 포인터는 늘 1개가 남게 되고, 이는 메모리 leak으로 이어지게 됨. 

- 해당코드 cat.mVar를 가르키는 포인터는 stack의의 pointer와 자기자신을 가르키는 포인터 두개

- 함수가 해제되면 stack위의 pointer는 메모리에서 사라지게 되고 heap에 남아있는 cat.mVar는 자기자신을 가르키는 포인터 1개가 영원히 남게 됨

- ref count가 1인채로 0이 될 수 없기 때문에 memory 안에 cat.mVar는 영원히 상주하게되어 메모리 릭이 일어남
