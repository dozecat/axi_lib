// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxis_async_fifo_tb.h for the primary calling header

#include "Vaxis_async_fifo_tb__pch.h"

// Parameter definitions for Vaxis_async_fifo_tb___024root
constexpr CData/*4:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_ENABLE;
constexpr CData/*4:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_FIFO_USE;
constexpr CData/*4:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__PTR_ZERO;
constexpr CData/*4:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__PTR_ONE;
constexpr CData/*4:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__PTR_ZERO;
constexpr CData/*4:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__PTR_ONE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__ID_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__DEST_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__USER_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__DEPTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__FRAME_FIFO;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__ALWAYS_RECEIVE;
constexpr VlWide<3>/*87:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__RAM_STYLE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__AUX_DEPTH;
constexpr VlWide<3>/*87:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__AUX_RAM_STYLE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__KEEP_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__STRB_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__FRAME_FIFO;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__ALWAYS_RECEIVE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__DEPTH;
constexpr VlWide<3>/*87:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__RAM_STYLE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_DEPTH;
constexpr VlWide<3>/*87:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_RAM_STYLE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__KEEP_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__STRB_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__ID_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__DEST_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__USER_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__LVLW;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_DEPTH_VAL;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_LVLW;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TDATA_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TKEEP_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TLAST_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TSTRB_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TID_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TDEST_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__D_TUSER_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__DATA_FIFO_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__A_TKEEP_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__A_TSTRB_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__A_TID_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__A_TDEST_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__A_TUSER_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__A_BAD_OFF;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_FIFO_RAW_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__AUX_FIFO_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__DEPTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__FWFT;
constexpr VlWide<3>/*87:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__RAM_STYLE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__AWID;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__PTRW;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__LVLW;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__DEPTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__FWFT;
constexpr VlWide<3>/*87:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__RAM_STYLE;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__AWID;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__PTRW;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb___024root::axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__LVLW;


void Vaxis_async_fifo_tb___024root___ctor_var_reset(Vaxis_async_fifo_tb___024root* vlSelf);

Vaxis_async_fifo_tb___024root::Vaxis_async_fifo_tb___024root(Vaxis_async_fifo_tb__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vaxis_async_fifo_tb___024root___ctor_var_reset(this);
}

void Vaxis_async_fifo_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vaxis_async_fifo_tb___024root::~Vaxis_async_fifo_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
