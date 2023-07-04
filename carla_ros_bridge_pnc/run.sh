source devel/setup.bash

# controller
rosrun controller controller control_method:="PurePursuit"
rosrun controller controller control_method:="Stanley"
rosrun controller controller control_method:="LQR"

# planning
rosrun planning planning