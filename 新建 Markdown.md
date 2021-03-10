# QT开发（三十九）——GraphicsView框架

​					[![img](https://s3.51cto.com//wyfs02/M00/80/1A/wKioL1c4Ef2AJRCzAAA8iIm8Ykg394_middle.jpg)](https://blog.51cto.com/9291927) 			

[天山老妖S](https://blog.51cto.com/9291927)关注0人评论[74661人阅读](javascript:;)[2016-12-03 14:43:59](javascript:;)

# ***\*QT开发（三十九）——\*******\*GraphicsView框架\****

  本文主要翻译自QT 5.6.2GraphicsView官方文档

## **一、*****\*GraphicsView框架\*******\*简介\****

QT4.2开始引入了Graphics View框架用来取代QT3中的Canvas模块，并作出了改进，Graphics View框架实现了模型－视图结构的图形管理，能对大量图元进行管理，支持碰撞检测，坐标变换和图元组等多种方便的功能。

[![wKioL1hCZ9mzslUwAADgkFOxTRs344.png](https://s4.51cto.com/wyfs02/M02/8B/05/wKioL1hCZ9mzslUwAADgkFOxTRs344.png)](https://s4.51cto.com/wyfs02/M02/8B/05/wKioL1hCZ9mzslUwAADgkFOxTRs344.png)

  GraphicsView框架结构主要包含三个主要的类QGraphicsScene（场景）、QGraphicsView（视图）、QGraphicsItem（图元）。QGraphicsScene本身不可见，是一个存储图元的容器，必须通过与之相连的QGraphicsView视图来显示及与外界进行交互，主要提供图元的操作接口、传递事件和管理各个图元状态，提供无变换的绘制功能（如打印）；QGraphicsView提供一个可视的窗口，用于显示场景中的图元，一个场景中可以有多个视图。QGraphicsItem是场景中各个图元的基础类，QT提供了常用图形图元的标准类，如矩形(QGraphicsRectItem)、椭（QGraphicsEllipseItem)、文本(QGraphicsTextItem)。

  GraphicsView是一个基于图元的Model/View架构的框架，每一个组件都是一个独立的元素。QPainter采用面向过程的描述方式绘图；GraphicsView采用面向对象的描述方式绘图。GraphicsView绘图时首先创建一个场景，然后创建图元对象（如一个直线对象、一个多边形对象），再使用场景的add()函数，将图元对象添加到场景中，最后通过视图进行显示。对于复杂的图像来说，如果图像包含大量的直线、曲线、多边形等图元对象，管理图元对象比管理QPainter的绘制过程语句要容易，并且图元对象更符合面向对象的思想，图形的可复用性更好。

## ***\*二、\*******\*QGraphicsScene\*******\*场景\****

  QGraphicsScene场景是QGraphicsItem对象的容器，主要功能如下： 

  A、提供管理大量图元的快速接口 

  B、传播鼠标、键盘等事件给场景中的每个图元 

  C、管理图元状态，如图元选择和焦点处理 

  D、提供无变换的渲染功能，如打印 

  通过函数QGraphicsScene::addItem()可以加入一个图元到场景中。图元可以通过多个函数进行检索：QGraphicsScene::items()及重载函数可以返回和点、矩形、多边形或向量路径相交的所有图元。QGraphicsScene::itemAt()返回指定点的最顶层图元。所有图元查找函数按照递减栈顺序返回图元，第一个返回的图元位置最顶层，最后一个返回的图元位于最底层。

  QGraphicsScene的事件传播体系将场景事件发送给图元，同时也管理图元之间的事件传播。如果场景收到了在某一点的鼠标单击事件，场景会把事件传给在这一点的最顶层图元。QGraphicsScene负责管理一些图元的状态，如图元选择和焦点。通过QGraphicsScene::setSeletionArea()函数选择多个图元，选择区域可以是任意的形状，使用 QPainterPath表示；要得到当前选择的图元列表可以使用 QGraphicsScene::selectedItems()函数；QGraphicsScene还管理图元的键盘输入焦点状态，可以通过QGraphicsScene::setFocusItem()函数或者QGraphicsItem::setFoucs()函数来设置图元的焦点；获得当前具有焦点的图元使用函数QGraphicsScene::foucsItem()。可以使用 QGraphicsScene::render()函数在绘图设备上绘制场景。 

## ***\*三、\*******\*QGraphicsView\*******\*视图\****

  QGraphicsView是视图窗口部件，使场景内容可视化，可以连接多个视图到一个场景，也可以为相同数据源的数据集提供不同的视图。QGraphicsView是可滚动的窗口部件，可以提供滚动条来浏览大的场景。如果需要使用OpenGL,可以使用QGraphicsView::setViewport()将视图设置为QGLWidget组件。

  视图接收键盘和鼠标的输入事件，并把事件翻译为场景事件(将坐标转换为场景的坐标)，再发送到场景。使用变换矩阵函数QGraphicsView::martix()可以变换场景的坐标系统,通过变换场景的坐标系统可以实现场景的缩放和旋转。为了方便，QGraphicsView提供了视图和场景的坐标转换函数：QGraphicsView::mapToScene()和QGraphicsView::mapFromScene()。 

## ***\*四、\*******\*QGraphicsItem\*******\*图元\****

  QGraphicsItem是图元的基类。QGraphics View框架提供了多种标准的图元： 

  QGraphicsEllipseItem 椭圆图元

 QGraphicsLineItem   直线图元

  QGraphicsPathItem   路径图元
  QGraphicsPixmapItem  图像图元

  QGraphicsPolygonItem 多边形图元
  QGraphicsRectItem   矩形图元
  QGraphicsSimpleTextItem 简单文本图元
  QGraphicsTextItem   文本浏览图元

  用户可以继承QGraphicsItem实现自定义的图元。

  QGraphicsItem图元主要特性如下： 

  A、支持鼠标按下、移动、释放、双击、悬停、滚动和右键菜单事件。 

  B、支持键盘输入焦点和按键事件 

  C、支持拖拽事件

  D、支持分组，使用父子关系和QGraphicsItemGroup

  E、支持碰撞检测 

  图元存在于本地坐标系统上，场景提供了在图元和场景间、图元与图元间进行坐标变换的函数。QGraphicsItem::transform()函数可以使用矩阵转换坐标系统。这对于翻转和缩放图元是有用的。

  图元可以包含其他图元，父图元的变换会被其所有的子图元继承。无论一个图元本身有多少变换，图元的所有函数（QGraphicsItem::contains(), QGraphicsItem::boundingRect(), QGraphicsItem::collidesWith()）仍旧执行在本地坐标系上。

  QGraphicsItem通过虚函数shape()和collideWith())来支持碰撞检测。从shape()返回图元的形状（以本地坐标QPainterPath表示），QGraphicsItem会处理所有的碰撞检测。如果要提供自己的碰撞检测，需要重新实现QGraphicsItem::collideWith()。

  碰撞检测的方法：

  a、重写shape()函数来返回图元的精准轮廓，依靠默认的collidesWithItem()来做外形交集。如果item轮廓和复杂时候，消耗是很大的。
  b、重写collidesWithItem()，提供一个自己的图元和轮廓碰撞的算法
Contains（）函数可以调用，用来决定一个图元是否包含一个点。Contains函数可以重写，contains()函数默认的方法是通过调用shape（）来完成的。
  图元中也可以包含其他的图元,也可以被别的图元包含，所有的图元可以有一个父类图元和多个子类图元,除非一个图元没有父类，否则图元的位置是在父类坐标中，子类图元将会继承父类图元的位置和转换。 

  通过调用setVisible()，可以设置图元是否可见，隐藏一个图元同时也隐藏了其子类，通过调用 setEnabled()来是指图元是否可用。如果禁用了图元，那么其所有的子类都不可用。图元默认都是可见和可用的。

## ***\*五、\*******\*GraphicsView坐标系统\****

  Graphics View坐标系基于笛卡尔坐标系，图元的场景中的位置和几何形状通过x坐标和y坐标表示。当使用没有变换的视图观察场景时，场景中的一个单位对应屏幕上的一个像素。

  Graphics View架构中有三个有效的坐标系统，图元坐标、场景坐标和视图坐标。Graphics View提供了三个坐标系统之间的转换函数。在绘制图形时，QGraphics View的场景坐标对应QPainter的逻辑坐标，QGraphics View的视图坐标对应QPainter的设备坐标。 

### ***\*1、\*******\*图元坐标\**** 

  图元存在于自己的本地坐标上，图元的坐标系统通常以图元中心为原点，图元中心也是所有坐标变换的原点，图元坐标方向是x轴正方向向右，y轴正方向向下。创建自定义图元时，只需要注意图元的坐标，QGraphicsScene和QGraphicsView会完成所有的变换。 例如，如果接受到一个鼠标按下或拖入事件，所给的事件位置是基于图元坐标系的。如果某个点位于图元内部，使用图元上的点作为QGraphicsItem::contains()虚函数的参数，函数会返回true。类似，图元的边界矩形和形状也是基于图元坐标系。

  图元的位置是图元的中心点在其父图元坐标系统的坐标。按这种说法，场景是所有无父图元的图元的父图元。顶层图元的位置是场景坐标。

[![wKioL1hCZ_6zyHecAACPjX725s4423.png](https://s3.51cto.com/wyfs02/M00/8B/05/wKioL1hCZ_6zyHecAACPjX725s4423.png)](https://s3.51cto.com/wyfs02/M00/8B/05/wKioL1hCZ_6zyHecAACPjX725s4423.png)



子图元的坐标与父图元的坐标相关。如果子图元无变换，子图元坐标和父图元坐标之间的区别与他们的父图元的坐标相同。例如，如果一个无变换的子图元精确的位于父图元的中心点，父子图元的坐标系统是相同的。如果子图元的位置是（10,0），子图元上的点（0,10）就是父图元上的点（10,10）。

由于图元的位置和变换与父图元相关，但子图元的坐标并不会被父图元的变换影响，虽然父图元的变换会隐式地变换子图元。在上例中，即使父图元被翻转和缩放，子图元上的点（0,10）仍旧是父图元上的点（10,10）。

  如果调用QGraphicsItem类的paint()函数重绘图元时，则以图元坐标系为基准。

### ***\*2、\*******\*场景坐标\**** 

  场景坐标是所有图元的基础坐标系统。场景坐标系统描述了顶层图元的位置，并且构成从视图传播到场景的所有场景事件的基础。每个图元在场景上都有场景坐标和边界矩形。场景坐标的原点在场景中心，坐标原点是X轴正方向向右，Y轴正方向向下。

[![wKiom1hCaBzznyLgAABQlPpPquk204.png](https://s3.51cto.com/wyfs02/M01/8B/09/wKiom1hCaBzznyLgAABQlPpPquk204.png)](https://s3.51cto.com/wyfs02/M01/8B/09/wKiom1hCaBzznyLgAABQlPpPquk204.png)

### **3、*****\*视图坐标\**** 

  视图坐标是窗口部件的坐标，视图坐标的单位是像素，QGraphicsView的左上角是(0,0)。所有鼠标事件、拖拽事件最开始都使用视图坐标，为了和图元交互，需要转换坐标为场景坐标。

[![wKiom1hCaDmQoeO3AABAsC66bUs857.png](https://s3.51cto.com/wyfs02/M00/8B/09/wKiom1hCaDmQoeO3AABAsC66bUs857.png)](https://s3.51cto.com/wyfs02/M00/8B/09/wKiom1hCaDmQoeO3AABAsC66bUs857.png)

### ***\*4、\*******\*坐标\*******\*变换\**** 

  在Graphics View框架中，经常需要将多种坐标变换，从场景到图元，从图元到图元，从视图到场景 。QGraphics View框架坐标变换函数如下：

QGraphicsView::mapToScene()视图到场景

QGraphicsView::mapFromScene() 场景到视图

QGraphicsItem::mapFromScene() 场景到图元

QGraphicsItem::mapToScene() 图元到场景

QGraphicsItem::mapToParent() 子图元到父图元

QGraphicsItem::mapFromParent() 父图元到子图元

QGraphicsItem::mapToItem()本图元到其他图元

QGraphicsItem::mapFromItem()其他图元到本图元

  在场景中处理图元时，从场景到图元、从图元到图元、从视图到场景进行坐标和图形变换是有用的。当在QGraphicsView的视口中点击鼠标时，应该通过调用QGraphicsView::mapToScence()与QGraphicsScene::itemAt()来获知光标下是场景中的哪个图元；如果想获知一个图元位于视口中的位置，应该先在图元上调用QGraphicsItem::mapToScene(),然后调用QGraphicsView::mapFromScene()；如果想获知在一个视图椭圆中有哪些图元,应该把QPainterPath传递到mapToScene(),然后再把映射后的路径传递到QGraphicsScene::items()。 可以调用QGraphicsItem::mapToScene()与QGraphicsItem::mapFromScene()在图元与场景之间进行坐标与形状的映射，也可以在子图元与其父图元之间通过QGraphicsItem::mapToParent()与QGraphicsItem::mapFromItem()进行映射。所有映射函数可以包括点、矩形、多边形、路径。视图与场景之间的映射也与此类似。对于视图与图元之间的映射，应该先从视图映射到场景，然后再从场景图映射到图元。

## ***\*六、\*******\*GraphicsView\*******\*框架特性\****

### **1、*****\*缩放与旋转\****

  QGraphicsView通过QGraphicsView::setMatrix()支持同QPainter一样的坐标变换，通过对一个视图应用变换，可以很容易地支持普通的导航特性如缩放与旋转。

### **2、*****\*打印\****

  图形视图架构通过渲染函数QGraphicsScene::render()和QGraphicsView::render()支持单行打印

场景和视图的渲染函数的不同在于QGraphicsScene::render()使用场景坐标，QGraphicsView::render()使用视图坐标。QGraphicsScene::render()经常用于打印未变换场景中的整块，例如一块图形数据或是打印一个文本文档。  QGraphicsView::render()适合用于截屏，默认会使用绘图设备精确渲染视口的内容。

QGraphicsScene scene;

scene.addRect(QRectF(0, 0, 100, 200), QPen(Qt::black), QBrush(Qt::green));

QPixmap pixmap;

QPainter painter(&pixmap);

painter.setRenderHint(QPainter::Antialiasing);

scene.render(&painter);

painter.end();

pixmap.save("scene.png");

  当源和目标区尺寸不匹配时，源的内容会比例缩放适合目标区。

### **3、*****\*拖拽\****

  由于QGraphicsView继承自QWidget,GraphicsView同样提供了拖拽功能。此外，为了方便，GraphicsView框架也为场景、图元提供拖拽支持。当视图接收到拖拽事件，GraphicsView框架会将拖拽事件翻译为QGraphicsSceneDragDropEvent事件,再发送到场景，场景接管事件，再把事件发送到光标下接受拖拽的第一个图元。
  为了开启图元拖拽，创建一个QDrag对象，传递启动拖拽的QWidget的指针。图元可以同时被多个视图观察，但只有一个视图可以拖拽图元。通常，拖拽是从按下鼠标或是移动鼠标开始的，在mousePressEvent()或mouseMoveEvent()中，可以从事件中得到原始的QWidget指针。

void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)

 {

   QMimeData *data = new QMimeData;

   data->setColor(Qt::green);

   QDrag *drag = new QDrag(event->widget());

   drag->setMimeData(data);

   drag->start();

 }

  要在场景中取拖拽事件，需要重新实现QGraphicsScene::dragEnterEvent()和QGraphicsItem子类里特定场景需要的事件处理器。

  图元也可以通过调用QGraphicsItem::setAcceptDrops()获得拖拽支持，为了处理将要进行的拖拽，需要重新实现QGraphicsItem的dragEnterEvent()、dragMoveEvent()、dropEvent()、dragLeaveEvent() 。

### **4、*****\*光标与工具提示\****

  QGraphicsItem支持光标（QgraphicsItem::setCursor)与工具提示(QGraphicsItem::setToolTip())。当光标进入到图元的区域，光标与工具提示被QGraphicsView激活（通过调用QGraphicsItem::contains()检测），也可以直接在视图上设置一个缺省光标(QGraphicsView::setCursor)。

### **5、*****\*动画\****

  GraphicsView框架支持多种层次的动画。使用动画框架可以很容易制作出动画。

GraphicsView框架支持的动画实现种类如下：

  A、图元需要继承自QGraphicsObject，并且需要联结QPropertyAnimation属性。

  B、创建继承自QObject和QGraphicsItem的图元，图元可以设置自己的定时器，在QObject::timeEvent()中增加步进的方式来控制动画。
  C、通过调用QGraphicsScene::advance()来推进场景，依次调用QGraphicsItem::advance()。

### ***\*6、\*******\*OpenGL渲染\****

  为了使用OpenGL渲染，需要设置一个新的QGLWidget作为QGraphicsView的视口：QGraphicsView::setViewPort()。如果需要OpenGL提供反锯齿功能，则需要OpenGL采样缓冲支持。
QGraphicsView view(&scene);
view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

### ***\*7、图元组\****

  通过把一个图元做为另一个图元的孩子，可以得到图元组的大多数本质特性：所有图元会一起移动，所有变换会从父到子传递。

  另外，QGraphicsItemGroup是一个特殊的图元。为了增加和删除图元，它使用一个有用接口合并了子图元的事件处理。把一个图元加到QGraphicsItemGroup仍会保留图元的原始位置与变换，而给一个图元重新指定父图元则会让图元根据其新的父亲重新定位。可以用QGraphicsScene::createItemGroup()创建图元组。

### 8、图形组件和布局

  QT4.4通过QGraphicsWidget支持图形和图元布局。QGraphicsWidget类似于QWidget，但QGraphicsWidget并不从QPaintDevice继承，而是继承自QGraphicsItem。QGraphicsWidget支持事件、信号与槽、大小和策略。通过QGraphicsLinearLayout、QGraphicsGridLayout可以对图形组件进行布局管理。

  QGraphicsWidget继承了QWidget和QGraphicsItem的优点，如QWidget的样式、字体、调色板、布局方向以及QGraphicsItem的图形、独立精度和变换支持。

  QGraphicsLayout是专为QGraphicsWidget特殊设计的第二代布局框架。QGraphicsLayout的API类似于QLayout。通过QGraphicsLinearLayout和QGraphicsGridLayout可以管理组件与子布局。

### **9、*****\*嵌入组件\****

图形视图框架为嵌入任何组件到场景提供了无缝支持。可以嵌入简单的组件，如QLineEdit、QPushButton，或是复杂的组件如QTableWidget，甚至是主窗口。

要嵌入组件到场景，只需要调用QGraphicsScene::addWidget()，或是创建一个QGraphicsProxyWidget实例，手动嵌入组件。

  通过QGraphicsProxyWidget，图形视图框架可以深度整合客户组件特性，如光标、工具提示、鼠标、平板和键盘事件、子组件、动画、弹拉框、组件输入焦点和激活。QGraphicsProxyWidget甚至整合了嵌入组件的tab顺序，可以通过tab选择嵌入的组件。甚至可以嵌入一个QGraphicsView到场景。

  当变换和嵌入组件时，图形视图框架会确保组件会被独立变换。