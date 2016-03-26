
## 1.Question 1：
**output**:
```
0x29fee8
0x29fee4
0x29fee8 
```
**解释**：
```
  ‘int a = 1’声明了一个栈变量a，其地址为0x29fee8，内容为1；‘int *ap = &a;’紧接着又声明了一个指针变量ap，
它有自己的地址0x29fee4（注意栈地址是向下增长的），内容为0x29fee8；‘int &ar = a;’再将a的引用传给新变量ar，
此时ar就指向了地址0x29fee8，内容为1（这相当于给a取了个别名，编译器每次读到ar的时候，就把它当成a处理（我一直
这么认为，感觉也很合理，可惜事实不然））。

    编译器（C++,其它的没见过）在处理引用的时候和处理指针是一样的，即在内存中申请一个空间，他有自己的地址（>0x29fee8），
内容为0x29fee8，然后编译器将ar和*ap做一样处理，&ar和ap做一样处理。如此伪装，好像ar和a指向了相同地址，没有为ar分配
空间。然后输出了上面的结果。（附件：main.cpp,main.s）
```
## 2.Question 2：
- 引用变量的地址不符合压栈规律，而是在栈底预留了一些空间。为了伪装成引用变量和原变量指向同一地址，没有为引用分配空间
这点也是必然的。否则ap的地址就不得不变为0x29fee0了。  
- 编译器对引用和指针做了相同的实现，但又要它们呈现给程序员的结果不一样，所以须将ar和*ap做一样处理，&ar和ap做一样处理。
取址操作符&对于引用来说变成了取值，用movl代替了leal（附件：main.cpp,main.s）。这样的反差将ar包装成了引用。
- 此外编译器对引用做了许多限制，造成许多程序员使用层面的不同，比如：
```
		a. A pointer can be re-assigned any number of times while a reference can not be re-seated after binding.
		b. Pointers can point everywhere including nowhere (NULL), whereas reference always refer to an object.
		c. You can't take the address of a reference like you can with pointers.
		d. There's no "reference arithmetics" (but you can take the address of an object pointed by a reference and
		   do pointer arithmetics on it as in &obj + 5).
```

## 3.problem 3：
**a.传值---传递基本数据类型参数**  
```
public  class  PassValue{  
    static void exchange(int a, int b){//静态方法，交换a,b的值  
        int temp;  
        temp = a;
        a = b;  
        b = temp;  
    }  
    public static void main(String[] args){  
       int i = 10;  
       int j = 100;  
       System.out.println("before call: " + "i=" + i + "\t" + "j = " + j);//调用前  
        exchange(i, j);      //值传递，main方法只能调用静态方法  
        System.out.println("after call: " + "i=" + i + "\t" + "j = " + j);//调用后  
    }  
}
```
运行结果：
```  
        before call: i = 10        j = 100    
        after    call: i = 10        j = 100  
```
说明：调用exchange(i, j)时，实际参数i，j分别把值传递给相应的形式参数a，b,在执行方法exchange()时，
形式参数a，b的值的改变不影响实际参数i和j的值，i和j的值在调用前后并没改变。

**b.引用传递---对象作为参数**  
如果在方法中把对象（或数组）作为参数，方法调用时，参数传递的是对象的引用（地址），即在方法调用时，
实际参数把对对象的引用（地址）传递给形式参数。这是实际参数与形式参数指向同一个地址，即同一个对象（数组），
方法执行时，对形式参数的改变实际上就是对实际参数的改变，这个结果在调用结束后被保留了下来。
```
class Book{
    String name;
    private folat price;
    Book(String n,    float ){                //构造方法
        name = n;
        price = p;
    }
    static  void  change(Book a_book,    String n,    float p){    //静态方法，对象作为参数
            a_book.name = n;
            a_book.price = p;
    }
    public void output(){        //实例方法，输出对象信息
        System.out.println("name: " + name + "\t" + "price: " + price);
    }
}
 public class PassAddr{
    public static void main(String [] args){
        Book b = new Book("java2",    32.5f);
        System.out.print("before call:\t");        //调用前
        b.output();
        b.change(b,    "c++",    45.5f);            //引用传递，传递对象b的引用，修改对象b的值
        System.out.print("after call:\t");            //调用后
        b.output();
    }
}
```
运行结果：  
```
        before    call:    name:java2        price:32.5    
        after       call:    name:c++          price:45.5  
```
说明：调用change(b,"c++",45.5f)时，对象b作为实际参数，把引用传递给相应的形式参数a_book,实际上a_book也指向同一个对象，
即该对象有两个引用名：b和a_book。在执行方法change()时，对形式参数a_book操作就是对实际参数b的操作。

**c.传引用-基本数据类型传引用**  
```
public  class  PassValue{
    static void exchange(int &a, int &b){//静态方法，交换a,b的值
        int temp;
        temp = a;
        a = b;
        b = temp;
    }
    public static void main(String[] args){
       int i = 10;
       int j = 100;
       System.out.println("before call: " + "i=" + i + "\t" + "j = " + j);//调用前
        exchange(i, j);      //值传递，main方法只能调用静态方法
        System.out.println("after call: " + "i=" + i + "\t" + "j = " + j);//调用后
    }
}
```
运行结果：
```
        before call: i = 10        j = 100
        after    call: i = 100       j = 10
```
说明：调用exchange(i, j)时，实际参数i，j分别把引用传递给相应的形式参数a，b,在执行方法exchange()时，
形式参数a，b的实际参数i和j指向相同地址，a,b改变，i,j也改变。

**d.相关说明**  
以上是使用规则。不体现编译器如何实现。编译器不为传递的应用参数分配内存可以实现上述效果，像C++那样
实现也可以实现上述效果