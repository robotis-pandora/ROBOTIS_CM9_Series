#ifndef _BOOTS_SEQUENCES_H_
#define _BOOTS_SEQUENCES_H_

#include "Boots_Poses.h"

/// Init
transition_t Boots_Init[] __FLASH__ = {{Boots_id,1},{Boots_Init_1,3000}};

/// Forward
transition_t Boots_Forward_I_R[] __FLASH__ = {{Boots_id,3},{Boots_Forward_I_R_1,72},{Boots_Forward_I_R_2,72},{Boots_Forward_I_R_3,96}};

transition_t Boots_Forward_I_L[] __FLASH__ = {{Boots_id,3},{Boots_Forward_I_L_1,72},{Boots_Forward_I_L_2,72},{Boots_Forward_I_L_3,96}};

transition_t Boots_Forward_R_L[] __FLASH__ = {{Boots_id,3},{Boots_Forward_R_L_1,72},{Boots_Forward_R_L_2,72},{Boots_Forward_R_L_3,72}};

transition_t Boots_Forward_L_R[] __FLASH__ = {{Boots_id,3},{Boots_Forward_L_R_1,72},{Boots_Forward_L_R_2,72},{Boots_Forward_L_R_3,72}};

transition_t Boots_Forward_R_I[] __FLASH__ = {{Boots_id,3},{Boots_Forward_R_I_1,96},{Boots_Forward_R_I_2,96},{Boots_Forward_R_I_3,96}};

transition_t Boots_Forward_L_I[] __FLASH__ = {{Boots_id,3},{Boots_Forward_L_I_1,96},{Boots_Forward_L_I_2,96},{Boots_Forward_L_I_3,96}};

/// Backward
transition_t Boots_Backward_I_R[] __FLASH__ = {{Boots_id,3},{Boots_Backward_I_R_1,96},{Boots_Backward_I_R_2,96},{Boots_Backward_I_R_3,96}};

transition_t Boots_Backward_I_L[] __FLASH__ = {{Boots_id,3},{Boots_Backward_I_L_1,96},{Boots_Backward_I_L_2,96},{Boots_Backward_I_L_3,96}};

transition_t Boots_Backward_R_L[] __FLASH__ = {{Boots_id,3},{Boots_Backward_R_L_1,96},{Boots_Backward_R_L_2,96},{Boots_Backward_R_L_3,96}};

transition_t Boots_Backward_L_R[] __FLASH__ = {{Boots_id,3},{Boots_Backward_L_R_1,96},{Boots_Backward_L_R_2,96},{Boots_Backward_L_R_3,96}};

transition_t Boots_Backward_R_I[] __FLASH__ = {{Boots_id,3},{Boots_Backward_R_I_1,96},{Boots_Backward_R_I_2,96},{Boots_Backward_R_I_3,96}};

transition_t Boots_Backward_L_I[] __FLASH__ = {{Boots_id,3},{Boots_Backward_L_I_1,96},{Boots_Backward_L_I_2,96},{Boots_Backward_L_I_3,96}};

/// Maneuvering
transition_t Boots_SpinRight[] __FLASH__ = {{Boots_id,3},{Boots_SpinRight_1,96},{Boots_SpinRight_2,72},{Boots_SpinRight_3,144}};

transition_t Boots_SpinLeft[] __FLASH__ = {{Boots_id,3},{Boots_SpinLeft_1,96},{Boots_SpinLeft_2,72},{Boots_SpinLeft_3,144}};

transition_t Boots_StrafeRight[] __FLASH__ = {{Boots_id,3},{Boots_StrafeRight_1,96},{Boots_StrafeRight_2,72},{Boots_StrafeRight_3,96}};

transition_t Boots_StrafeLeft[] __FLASH__ = {{Boots_id,3},{Boots_StrafeLeft_1,96},{Boots_StrafeLeft_2,72},{Boots_StrafeLeft_3,96}};

/// Offense
transition_t Boots_F_Shoot_R[] __FLASH__ = {{Boots_id,7},{Boots_F_Shoot_R_1,72},{Boots_F_Shoot_R_2,96},{Boots_F_Shoot_R_3,96},{Boots_F_Shoot_R_4,96},{Boots_F_Shoot_R_5,400},{Boots_F_Shoot_R_6,96},{Boots_F_Shoot_R_7,496}};

transition_t Boots_F_Shoot_L[] __FLASH__ = {{Boots_id,7},{Boots_F_Shoot_L_1,72},{Boots_F_Shoot_L_2,96},{Boots_F_Shoot_L_3,96},{Boots_F_Shoot_L_4,96},{Boots_F_Shoot_L_5,400},{Boots_F_Shoot_L_6,96},{Boots_F_Shoot_L_7,496}};

transition_t Boots_R_Shoot[] __FLASH__ = {{Boots_id,5},{Boots_R_Shoot_1,72},{Boots_R_Shoot_2,96},{Boots_R_Shoot_3,96},{Boots_R_Shoot_4,96},{Boots_R_Shoot_5,496}};

transition_t Boots_L_Shoot[] __FLASH__ = {{Boots_id,5},{Boots_L_Shoot_1,72},{Boots_L_Shoot_2,96},{Boots_L_Shoot_3,96},{Boots_L_Shoot_4,96},{Boots_L_Shoot_5,496}};

transition_t Boots_Pass_R[] __FLASH__ = {{Boots_id,6},{Boots_Pass_R_1,400},{Boots_Pass_R_2,96},{Boots_Pass_R_3,96},{Boots_Pass_R_4,96},{Boots_Pass_R_5,200},{Boots_Pass_R_6,496}};

transition_t Boots_Pass_L[] __FLASH__ = {{Boots_id,6},{Boots_Pass_L_1,400},{Boots_Pass_L_2,96},{Boots_Pass_L_3,96},{Boots_Pass_L_4,96},{Boots_Pass_L_5,200},{Boots_Pass_L_6,496}};

transition_t Boots_B_Shoot_R[] __FLASH__ = {{Boots_id,7},{Boots_B_Shoot_R_1,400},{Boots_B_Shoot_R_2,96},{Boots_B_Shoot_R_3,96},{Boots_B_Shoot_R_4,96},{Boots_B_Shoot_R_5,96},{Boots_B_Shoot_R_6,96},{Boots_B_Shoot_R_7,496}};

transition_t Boots_B_Shoot_L[] __FLASH__ = {{Boots_id,7},{Boots_B_Shoot_L_1,400},{Boots_B_Shoot_L_2,96},{Boots_B_Shoot_L_3,96},{Boots_B_Shoot_L_4,96},{Boots_B_Shoot_L_5,96},{Boots_B_Shoot_L_6,96},{Boots_B_Shoot_L_7,496}};

/// Defense
transition_t Boots_D_Ready[] __FLASH__ = {{Boots_id,1},{Boots_D_Ready_1,400}};

transition_t Boots_D_Right[] __FLASH__ = {{Boots_id,3},{Boots_D_Right_1,72},{Boots_D_Right_2,72},{Boots_D_Right_3,72}};

transition_t Boots_D_Front[] __FLASH__ = {{Boots_id,3},{Boots_D_Front_1,72},{Boots_D_Front_2,72},{Boots_D_Front_3,72}};

transition_t Boots_D_Left[] __FLASH__ = {{Boots_id,3},{Boots_D_Left_1,72},{Boots_D_Left_2,72},{Boots_D_Left_3,72}};


#endif
