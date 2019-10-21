#include "font_basic.h"

uint8_t ft_basic_space_data[] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0 };

uint8_t ft_basic_a_data[] = { 0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0 };

uint8_t ft_basic_b_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_c_data[] = { 0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_d_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_e_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0 };

uint8_t ft_basic_f_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0 };

uint8_t ft_basic_g_data[] = { 0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_h_data[] = { 0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0 };

uint8_t ft_basic_i_data[] = { 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0 };

uint8_t ft_basic_j_data[] = { 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0,    0,    0, 0 };

uint8_t ft_basic_k_data[] = { 0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0 };

uint8_t ft_basic_l_data[] = { 0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0 };

uint8_t ft_basic_m_data[] = { 0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0xFF, 0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF, };

uint8_t ft_basic_n_data[] = { 0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF, };

uint8_t ft_basic_o_data[] = { 0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_p_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0 };

uint8_t ft_basic_q_data[] = { 0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0xFF, 0xFF, 0 };

uint8_t ft_basic_r_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0 };

uint8_t ft_basic_s_data[] = { 0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0,    0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0,    0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,    0 };

uint8_t ft_basic_t_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_u_data[] = { 0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0 };

uint8_t ft_basic_v_data[] = { 0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0,    0,    0xFF, 0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_w_data[] = { 0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0,    0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0,    0xFF, 0,    0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                              0, 0,    0xFF, 0xFF, 0,    0xFF, 0xFF, 0 };

uint8_t ft_basic_x_data[] = { 0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0 };

uint8_t ft_basic_y_data[] = { 0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0,    0 };

uint8_t ft_basic_z_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0,    0,    0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0,    0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0 };

uint8_t ft_basic_0_data[] = { 0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0,    0,    0xFF, 0xFF, 0,
                              0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0 };

uint8_t ft_basic_1_data[] = { 0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0 };

uint8_t ft_basic_2_data[] = { 0, 0,    0xFF, 0xFF, 0xFF, 0,    0, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0xFF, 0xFF, 0,    0xFF, 0xFF, 0, 0,
                              0, 0,    0,    0,    0xFF, 0xFF, 0, 0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0, 0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0 };

uint8_t ft_basic_3_data[] = { 0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0,    0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0,    0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0,
                              0, 0, 0,    0,    0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0,    0xFF, 0xFF, 0, 0,
                              0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0,
                              0, 0, 0,    0xFF, 0xFF, 0,    0, 0 };

uint8_t ft_basic_4_data[] = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0,    0,    0,    0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0,    0xFF, 0xFF, 0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0,    0xFF, 0xFF, 0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0,    0,
                              0, 0,    0xFF, 0xFF, 0,    0,    0,    0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                              0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0 };
void ft_basic_install()
{
    ft_basic.charheight = 10;
    ft_basic.charwidth  = 8;
    ft_basic.numchar    = 0;

    ft_add_char(&ft_basic, ft_basic_space_data, ' ');
    ft_add_char(&ft_basic, ft_basic_a_data, 'a');
    ft_add_char(&ft_basic, ft_basic_b_data, 'b');
    ft_add_char(&ft_basic, ft_basic_c_data, 'c');
    ft_add_char(&ft_basic, ft_basic_d_data, 'd');
    ft_add_char(&ft_basic, ft_basic_e_data, 'e');
    ft_add_char(&ft_basic, ft_basic_f_data, 'f');
    ft_add_char(&ft_basic, ft_basic_g_data, 'g');
    ft_add_char(&ft_basic, ft_basic_h_data, 'h');
    ft_add_char(&ft_basic, ft_basic_i_data, 'i');
    ft_add_char(&ft_basic, ft_basic_j_data, 'j');
    ft_add_char(&ft_basic, ft_basic_k_data, 'k');
    ft_add_char(&ft_basic, ft_basic_l_data, 'l');
    ft_add_char(&ft_basic, ft_basic_m_data, 'm');
    ft_add_char(&ft_basic, ft_basic_m_data, 'n');
    ft_add_char(&ft_basic, ft_basic_o_data, 'o');
    ft_add_char(&ft_basic, ft_basic_p_data, 'p');
    ft_add_char(&ft_basic, ft_basic_q_data, 'q');
    ft_add_char(&ft_basic, ft_basic_r_data, 'r');
    ft_add_char(&ft_basic, ft_basic_s_data, 's');
    ft_add_char(&ft_basic, ft_basic_t_data, 't');
    ft_add_char(&ft_basic, ft_basic_u_data, 'u');
    ft_add_char(&ft_basic, ft_basic_v_data, 'v');
    ft_add_char(&ft_basic, ft_basic_w_data, 'w');
    ft_add_char(&ft_basic, ft_basic_x_data, 'x');
    ft_add_char(&ft_basic, ft_basic_y_data, 'y');
    ft_add_char(&ft_basic, ft_basic_z_data, 'z');
    // numeric
    ft_add_char(&ft_basic, ft_basic_0_data, '0');
    ft_add_char(&ft_basic, ft_basic_1_data, '1');
    ft_add_char(&ft_basic, ft_basic_2_data, '2');
    ft_add_char(&ft_basic, ft_basic_3_data, '3');
} /* ft_basic_install */
