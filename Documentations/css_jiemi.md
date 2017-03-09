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

