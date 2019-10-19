#include "font_basic.h"

void ft_basic_install()
{
    ft_basic.charheight = 10;
    ft_basic.charwidth  = 8;
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
                                  0, 0,    0xFF, 0,    0xFF, 0,    0xFF, 0,
                                  0, 0,    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                                  0, 0,    0,    0xFF, 0xFF, 0xFF, 0,    0,
                                  0, 0,    0,    0xFF, 0,    0xFF, 0,    0 };

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
} /* ft_basic_install */
