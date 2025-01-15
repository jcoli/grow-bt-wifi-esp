/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#ifndef __CONTROL_H__
#define __CONTROL_H__

void on_receive_master(String line_in);
void update_variables(String line);
void update_variables_service0(String line);
void update_variables_service1(String line);
void update_variables_service2(String line);
void update_variables_service3(String line);
void update_variables_service4(String line);
void update_variables_service5(String line);
void update_variables_service6(String line);
void update_variables_service7(String line);
void on_bit_alive_bt();
void on_bit_connected_bt();
void decoder_one();
void decoder_two();
void decoder_three();
void decoder_four();
void decoder_five();
#endif