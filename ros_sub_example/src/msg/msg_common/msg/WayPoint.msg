float64 x			#路径x坐标
float64 y			#路径y坐标
float64 z			#路径z坐标
float64 left			#距左边界值
float64 right			#距右边界值
float32 heading_angle		#路径的方向
float32 curvature		#曲率
float32 speed			#路径的速度
float32 distance		#路点与路径起点沿路径的距离
float32 slope			#坡度信息
uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)
float32 speed_limit	        #速度上限
bool direction			#0表示前进，1表示后退
uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点
float64 t			#时间
string area_name		#区域名称	
string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	
