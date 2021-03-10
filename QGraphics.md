https://blog.csdn.net/qq_17813937/article/details/51370106

# QGraphicsView 透明背景和边框

 view->setStyleSheet("padding:0px;border:0px"); 

# 在QGraphicsView里写paintEvent 为什么画不出来啊

QPainter painter(this->viewport());

最好不要重写QGraphicsView的paintEvent，而是考虑 QGraphicsScene::drawBackground, QGraphicsScene::drawForeground，或者 QGraphicsItem 



# QGraphicsView::translate() does nothing
setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
translate(1,1);
		
# Scene的大小在变
插入item的时候，是Scene的大小在变，view是不会变的，所以我估计楼主的烦恼应该是插入item的时候，view会弹出拖动条，而不是要去固定view的尺寸。
所以应该用QGraphicsView::setSceneRect()这个函数，固定住view的可视范围，就不会弹出拖动条了。

# 当前x

```
qreal x = sceneRect().width() * (horizontal->value() - horizontal->minimum())/
            (qreal)(horizontal->maximum() - horizontal->minimum() + horizontal->pageStep());
```

 

# 场景索引算法

场景使用一个索引算法(indexing algorithm)有效的管理Item的位置. 默认使用BSP树(二进制空间分区).这种算法适用于场景中

的Item处于静止. 你可以选择禁用这些索引使用函数setItemIndexMethod().关于索引算法的更多信息，查看itemIndexMethod属性

https://blog.csdn.net/can3981132/article/details/52592555





 Qt中事件传递是由父向子传递，同样在视图场景中事件传递是View->Scene->Item这样的顺序，所以上层的事件函数重写必须调用父类事件函数，实现事件的向下传递，不至于阻塞后面元素的事件处理。 





 在View中调用setBackgroundBrush方法会阻止Scene中drawBackground方法的调用，这个帮助中有说明，属于帮助看的不仔细。另外View/Scene中的drawBackground和drawForeground方法类似事件函数，调用顺序是View->Scene，所以在自定义View中drawBackground和drawForeground方法时需要调用父类方法。
————————————————
版权声明：本文为CSDN博主「Coding_Night」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/wry323/java/article/details/78444070





 QGraphicsScene::sceneRect和QGraphicsView::sceneRect是有区别的，QGraphicsScene::sceneRect是场景的实际范围大小，是一个抽象逻辑概念，例如用场景作为画布，为画布的实际大小。QGraphicsView::sceneRect则是在View中需要给Scene预留的区域大小，这个类似窗口概念，QGraphicsView::sceneRect的大小直接影响则View窗口中滚动条的出现。在开发中QGraphicsScene::sceneRect最好小于等于QGraphicsView::sceneRect大小，以保证在缩放View时通过滚动条可以查看到完整的Scene区域。
————————————————
版权声明：本文为CSDN博主「Coding_Night」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/wry323/java/article/details/78444070



# 如何使QGraphicsItem不随QGraphicsView放大缩小而改变大小

https://blog.csdn.net/goforwardtostep/article/details/76862952



# QGraphicsItemke绘制可见区域

https://doc.qt.io/qt-5/qrectf.html
QStyleOptionGraphicsItem::exposedRect

This variable holds the exposed rectangle, in item coordinates

Make use of this rectangle to speed up item drawing when only parts  of the item are exposed. If the whole item is exposed, this rectangle  will be the same as [QGraphicsItem::boundingRect](https://doc.qt.io/qt-5/qgraphicsitem.html#boundingRect)().

This member is only initialized for items that have the [QGraphicsItem::ItemUsesExtendedStyleOption](https://doc.qt.io/qt-5/qgraphicsitem.html#GraphicsItemFlag-enum) flag set.



# 多个item之间的层次

 setZValue()设置item的栈顺序，通过zValue()来测试，具有低z-values的item比具有高z-value的item先绘制。（即：低z-values的item位于下层，高z-values的item位于上层） 

 可以调用setZvalue()来设置一个item的Z值。默认的Z值是0，具有同样的Z值的item会按照插入的顺序来入栈(stack  order)。也就是说，GraphicsView会优先根据item的Z值决定item的层次，只有当Z值相同的情况下才会去理会stack  order； 

 API有一个stackBefore(QGraphicsItem *sibling)  方法，可以调用该访求来重新排序item的列表，就可以直接调整item的顺序了。例如：itemA->stackBefore(itemB)，是将itemA的order重置到itemB之前，这样，先绘制itemA，后绘制itemB，itemB处于上方。 





https://www.jianshu.com/p/05f680cf1f88

https://blog.csdn.net/Finull1/article/details/106640723

# 

```
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);//线性索引

    view.setRenderHint(QPainter::Antialiasing);//抗锯齿
    view.setCacheMode(QGraphicsView::CacheBackground);//缓存模式
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);//场景重绘更新方式
    view.setDragMode(QGraphicsView::ScrollHandDrag);//拖动模式，鼠标可拖动
    
    QRectF boundingRect() const;//预计绘制的区域
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);//绘制

五种模式，很容易理解：
QGraphicsView::FullViewportUpdate 全视口更新，整体都更新的意思啦
QGraphicsView::MinimalViewportUpdate 最小更新，哪里有变动更新哪里
QGraphicsView::SmartViewportUpdate 智能选择，它要自己选
QGraphicsView::BoundingRectViewportUpdate 来了，来了，它就是我们要注意的。
QGraphicsView::NoViewportUpdate 不更新

```

# QT自定义图形项中的boundingRect()和shape()函数的理解

https://blog.csdn.net/weixin_39583140/article/details/93599949

实现自定义图形项经常需要重绘的函数有boundingRect()、paint()、shape()。
针对霍亚飞的Qt creator中所说，boundingRect()函数具有以下特点：
1.paint绘制的图像必须在boundingRect()函数之中。
2.用来确定哪些区域需要重构（repaint）。
3.用来检测碰撞

# QGraphicsItem的paint

在QGraphicsScene重绘绘制时，需要调用其中的每一个QGraphicsItem的paint()函数来逐个重新绘制组件。这个函数的参数 中，painter是绘图设备的painter，option定义了一些绘图参数，如绘图区域大小等，而widget则是绘图设备本身，paint()函 数实际上就是用painter在widget上画一个图，图形的具体内容则有paint()的具体实现确定。不同的QGrahpicsItem的子类对 paint()函数做了不同的实现，我们也可以按照自己的需要，实现自己的paint()函数（比如原来实现效率太低需要实现一个高效率的版本等等），比如我们可以考虑给paint函数里所在的类设置一个类成 员函数指针，在paint中调用这个成员函数指针来给程序增加一些灵活定等等。
————————————————
版权声明：本文为CSDN博主「socrates」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/socrates/java/article/details/1999845

# QStyleOptionGraphicsItem exposedRect

```
可见绘制区域，如果QGraphicsView::MinimalViewportUpdate 最小更新，哪里有变动更新哪里则是，最小区域
```



# QGraphicsItem限制拖动方向和位置

https://blog.csdn.net/gdizcm/article/details/85869733



#  QGraphicsItem flag

```
 QGraphicsItem::ItemSendsScenePositionChanges//
 ItemIsMovable//可以移动
 ItemIsSelectable//选择
```





#  QGraphicsItem



https://blog.csdn.net/qq_17813937/article/details/51370106

# 坐标

```

GraphicsView::mapToScene() - 视图 -> 场景

QGraphicsView::mapFromScene() -  场景 -> 视图

QGraphicsItem::mapFromScene() -  场景 -> 图元

QGraphicsItem::mapToScene() - 图元 -> 场景

QGraphicsItem::mapToParent() - 子图元 -> 父图元

QGraphicsItem::mapFromParent() - 父图元 -> 子图元

QGraphicsItem::mapToItem() - 本图元 -> 其他图元

QGraphicsItem::mapFromItem() - 其他图元 -> 本图元

```

https://blog.csdn.net/lxj362343/article/details/106780692





#  定点缩放

https://www.jianshu.com/p/05f680cf1f88

https://blog.csdn.net/yangzijiangtou/article/details/104636033

# 拖动  鼠标点缩放

https://blog.csdn.net/xi__q/article/details/84289935



# GraphicsView translate

```
 setTransformationAnchor(QGraphicsView::NoAnchor);
translate(10,0);//看到scen左边的的，
滚动条：最值会改变
```

#translate

```
   setTransformationAnchor(QGraphicsView::NoAnchor);
    auto end = mapToScene(QPoint(this->width(), 0));
    auto start = mapToScene(QPoint(0, 0));
    qDebug()<<horizontalScrollBar()->value()没变
    //maximum()<<horizontalScrollBar()->minimum()<<<horizontalScrollBar()->maximum()<<horizontalScrollBar()->minimum()<< horizontalScrollBar()->pageStep();
    this->translate(end.x() - start.x(), 0);
    //horizontalScrollBar()->value()没变
    //maximum()   minimum()改变了了
```

#

在QGraphicsItem中mouseMoveEvent中调用view 的scale或者tranlete会崩 不知道为啥



# 模态





```
 item->setFlags(ItemIsPanel);
 item->setPanelModality(QGraphicsItem::SceneModal);
scene->addItem(item);
```





# setFlag(ItemHasNoContents);

不会调用paint；

# paint 模糊问题

如果坐标位置在屋里像素的小数位置就会模糊。