## CSS Secrets

> *What is CSS ?*
>
> CSS 全称 Cascading Style Sheet

### Introduction
* Vendor prefixes were an epic failure.

* Minimize code duplication

* 单位用em，随font-size动态变化。

* 半透明效果用 hsla 方法

* 响应式设计 (Responsive Web Design)

* 减少 “media” 指令的使用：
    1. 使用百分比宽度而不是固定宽度, 如果一定要固定宽度，尽量使用 vw, wh, vmax, vmin 这些 viewport-relative units。
    2. 当你想让某个元素变大时，使用 max-width, 而不是 width。
    3. 不要忘了给那些可置换元素设置max-width属性为100%。比如：img, object, video, iframe。
    4. 当背景图需要覆盖整个容器时，用 background-size: cover。最好不要把大图小化当移动终端的背景，浪费流量。
    5. When laying out images (or other elements) in a grid of rows and columns, let the number of columns be dictated by the viewport width. Flexible Box Layout (a.k.a. Flexbox) or display: inline-block and regular text wrapping can help with that.
    6. 当用多栏文本时，用 column-width 而不是 column-count，从而你在低分辨率的屏幕上能单栏显示。

* 在考虑响应式之前，你应该更多的保证你的设计足够的 “liquid”, 即别设计得太死板，如果所有参数都钉死了，就是太 “solid” 了。

### Backgrounds & Borders

* Translucent Borders

> What is RGBA & HSLA ?
>
> RGBA 实际上是 RGB + A，其中RGB代表由红、绿、蓝组成的颜色空间，A代表不透明度。
> HSLA 实际上是 HSL + A，其中HSL是工业界的颜色标准，由H-色相，S-饱和度，L-明度组成，A代表不透明度。

    
    ![Box Model](images/css_jiemi/box_model.png)

    * _The Problem_ : 当我们设置以下样式时，并不能得到半透明的边框。
            
            border: 10px solid hsla(0, 0%, 100%, 0.5);
            background: white;

    * _The Solution_ : 得不到半透明的边框并不是上面的样式出问题了，而是背景并没有延伸到边框下来，浏览器背景默认渲染到 border edge, 而我们需要渲染到 padding edge, 所以以下样式会起作用。

            border: 10px solid hsla(0, 0%, 100%, 0.5);
            background: white;
            background-clip: padding-box;

* Multiple Borders

> How to use Box-Shadow ?
>
> `box-shadow: h-shadow, v-shadow, [blur, spread, color, inset]`
>
> 其中，带方括号的为可选参数，h-shadow 表示阴影水平平移, v-shadow 表示阴影垂直平移, blur 表示模糊半径, spread 表示阴影半径, color 表示阴影颜色, inset 表示阴影方向为内敛( outset 为向外发散，互斥)

    * _The Problem_ : 当我们需要多重边框时，我们需要用多于的元素来嵌套实现，这种实现方式十分丑陋。

    * _The Solution_ : 
        
        * 使用 box-shadow 来解决:
            
            ![multi border box shadow](images/css_jiemi/multi_border_box_shadow.png)
    
                background: yellowgreen;
                box-shadow: 0 0 0 10px #655,
                            0 0 0 15px deeppink,
                            0 5px 10px 15px rgba(0,0,0,.6);

            * 因为这个方法只是模拟边框的视觉效果，所以实际使用是它所占的空间并不会被真正的去计算，不能和真正的border等同，需要利用 padding 或者 margin 来调整大小以和全局协调。

        * 使用 outline 来解决: 

            ![multi border outline](images/css_jiemi/multi_border_box_shadow.png)

                    background: yellowgreen;
	                border: 10px solid #655;
	                outline: 15px solid deeppink;
	                border-radius:10px

            * 利用 outline 方法只能得到二重边框，无法得到多重边框，同时可以看到，border-radius 没有影响到 outline 的表达，这是一个bug。

* Flexsible Backgroud Position

> How to use background-position ?
>
> `background-position: bottom right`, 这将会把背景放到容器右下角。

    * _The Problem_ : 如何让背景图偏离边界一点？

    * _The Solution_ :

        * 使用CSS3扩展的background-postion语法解决:

                background: url(code-pirate.svg) no-repeat #58a;
                background-position: right 20px bottom 10px;

        * 使用 background-origin 语法解决: 这种方法能省去每次调节 padding 大小的时候都要去调节 offset 的麻烦

                padding: 10px;
                background: url("code-pirate.svg") no-repeat #58a 
                            bottom right; /* or 100% 100% */
                background-origin: content-box; 

        * 使用 calc() 方法: 这种方法是始终以左上角为参照，利用 calc() 方法动态计算偏移值，注意+,-前后都必须有空格。 
                
                background: url("code-pirate.svg") no-repeat;
                background-position: calc(100% - 20px) calc(100%-10px);

* Inner Rounding

    * _The Problem_ : 如何让容器边框实现内圆外方的效果 ？

    * _The Solution_ : 

        * 使用两次嵌套的方法可以实现这种效果。

        * 使用 box-shadow + outline 解决:

            ![inner rounding](images/css_jiemi/inner_rounding.png)

                background: tan;
                border-radius: .8em;
                padding: 1em;
                box-shadow: 0 0 0 .6em #655;
                outline: .6em solid #655;
