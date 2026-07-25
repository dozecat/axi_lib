// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaxis_async_fifo_tb__Syms.h"


void Vaxis_async_fifo_tb___024root__trace_chg_0_sub_0(Vaxis_async_fifo_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vaxis_async_fifo_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root__trace_chg_0\n"); );
    // Body
    Vaxis_async_fifo_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxis_async_fifo_tb___024root*>(voidSelf);
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vaxis_async_fifo_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaxis_async_fifo_tb___024root__trace_chg_0_sub_0(Vaxis_async_fifo_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root__trace_chg_0_sub_0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    bufp->chgBit(oldp+0,(vlSelfRef.s_clk));
    bufp->chgBit(oldp+1,(vlSelfRef.s_rst));
    bufp->chgQData(oldp+2,(vlSelfRef.s_axis_tdata),64);
    bufp->chgCData(oldp+4,(vlSelfRef.s_axis_tkeep),8);
    bufp->chgCData(oldp+5,(vlSelfRef.s_axis_tstrb),8);
    bufp->chgBit(oldp+6,(vlSelfRef.s_axis_tlast));
    bufp->chgCData(oldp+7,(vlSelfRef.s_axis_tid),8);
    bufp->chgBit(oldp+8,(vlSelfRef.s_axis_tdest));
    bufp->chgBit(oldp+9,(vlSelfRef.s_axis_tuser));
    bufp->chgBit(oldp+10,(vlSelfRef.s_axis_tvalid));
    bufp->chgBit(oldp+11,(vlSelfRef.s_axis_tready));
    bufp->chgBit(oldp+12,(vlSelfRef.m_clk));
    bufp->chgBit(oldp+13,(vlSelfRef.m_rst));
    bufp->chgQData(oldp+14,(vlSelfRef.m_axis_tdata),64);
    bufp->chgCData(oldp+16,(vlSelfRef.m_axis_tkeep),8);
    bufp->chgCData(oldp+17,(vlSelfRef.m_axis_tstrb),8);
    bufp->chgBit(oldp+18,(vlSelfRef.m_axis_tlast));
    bufp->chgCData(oldp+19,(vlSelfRef.m_axis_tid),8);
    bufp->chgBit(oldp+20,(vlSelfRef.m_axis_tdest));
    bufp->chgBit(oldp+21,(vlSelfRef.m_axis_tuser));
    bufp->chgBit(oldp+22,(vlSelfRef.m_axis_tvalid));
    bufp->chgBit(oldp+23,(vlSelfRef.m_axis_tready));
    bufp->chgCData(oldp+24,(vlSelfRef.s_level),5);
    bufp->chgBit(oldp+25,(vlSelfRef.s_overflow));
    bufp->chgCData(oldp+26,(vlSelfRef.s_aux_level),5);
    bufp->chgBit(oldp+27,(vlSelfRef.s_aux_overflow));
    bufp->chgBit(oldp+28,(vlSelfRef.s_bad_frame));
    bufp->chgBit(oldp+29,(vlSelfRef.s_good_frame));
    bufp->chgCData(oldp+30,(vlSelfRef.m_level),5);
    bufp->chgBit(oldp+31,(vlSelfRef.m_underflow));
    bufp->chgCData(oldp+32,(vlSelfRef.m_aux_level),5);
    bufp->chgBit(oldp+33,(vlSelfRef.m_aux_underflow));
    bufp->chgBit(oldp+34,(vlSelfRef.m_bad_frame));
    bufp->chgBit(oldp+35,(vlSelfRef.m_good_frame));
    bufp->chgIData(oldp+36,(vlSelfRef.tb_depth),32);
    bufp->chgBit(oldp+37,(vlSelfRef.tb_frame_fifo));
    bufp->chgBit(oldp+38,(vlSelfRef.tb_always_recv));
    bufp->chgIData(oldp+39,(vlSelfRef.tb_data_width),32);
    bufp->chgCData(oldp+40,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_data),8);
    bufp->chgCData(oldp+41,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tstrb),8);
    bufp->chgCData(oldp+42,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tid),8);
    bufp->chgBit(oldp+43,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tdest));
    bufp->chgBit(oldp+44,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tuser));
    bufp->chgBit(oldp+45,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_bad_frame));
    bufp->chgBit(oldp+46,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty));
    bufp->chgBit(oldp+47,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_en_fsm));
    bufp->chgCData(oldp+48,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__frame_tkeep),8);
    bufp->chgCData(oldp+49,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__frame_tstrb),8);
    bufp->chgCData(oldp+50,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__frame_tid),8);
    bufp->chgBit(oldp+51,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__frame_tdest));
    bufp->chgBit(oldp+52,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__frame_tuser));
    bufp->chgBit(oldp+53,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__frame_is_bad));
    bufp->chgBit(oldp+54,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en));
    bufp->chgWData(oldp+55,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data),83);
    bufp->chgBit(oldp+58,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full));
    bufp->chgBit(oldp+59,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_overflow));
    bufp->chgCData(oldp+60,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_level),5);
    bufp->chgBit(oldp+61,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en));
    bufp->chgWData(oldp+62,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data),83);
    bufp->chgBit(oldp+65,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty));
    bufp->chgBit(oldp+66,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_underflow));
    bufp->chgCData(oldp+67,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level),5);
    bufp->chgQData(oldp+68,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdata),64);
    bufp->chgBit(oldp+70,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tlast));
    bufp->chgCData(oldp+71,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tkeep),8);
    bufp->chgCData(oldp+72,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tstrb),8);
    bufp->chgCData(oldp+73,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tid),8);
    bufp->chgBit(oldp+74,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdest));
    bufp->chgBit(oldp+75,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tuser));
    bufp->chgIData(oldp+76,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i),32);
    bufp->chgCData(oldp+77,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp),5);
    bufp->chgCData(oldp+78,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr),5);
    bufp->chgCData(oldp+79,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray),5);
    bufp->chgCData(oldp+80,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_ms),5);
    bufp->chgCData(oldp+81,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_rd),5);
    bufp->chgCData(oldp+82,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr),5);
    bufp->chgCData(oldp+83,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray),5);
    bufp->chgCData(oldp+84,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_ms),5);
    bufp->chgCData(oldp+85,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_wr),5);
    bufp->chgCData(oldp+86,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin),5);
    bufp->chgCData(oldp+87,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin),5);
    bufp->chgWData(oldp+88,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0]),83);
    bufp->chgWData(oldp+91,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[1]),83);
    bufp->chgWData(oldp+94,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[2]),83);
    bufp->chgWData(oldp+97,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[3]),83);
    bufp->chgWData(oldp+100,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[4]),83);
    bufp->chgWData(oldp+103,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[5]),83);
    bufp->chgWData(oldp+106,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[6]),83);
    bufp->chgWData(oldp+109,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[7]),83);
    bufp->chgWData(oldp+112,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[8]),83);
    bufp->chgWData(oldp+115,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[9]),83);
    bufp->chgWData(oldp+118,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[10]),83);
    bufp->chgWData(oldp+121,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[11]),83);
    bufp->chgWData(oldp+124,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[12]),83);
    bufp->chgWData(oldp+127,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[13]),83);
    bufp->chgWData(oldp+130,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[14]),83);
    bufp->chgWData(oldp+133,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[15]),83);
    bufp->chgIData(oldp+136,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i),32);
    bufp->chgBit(oldp+137,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full));
    bufp->chgBit(oldp+138,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow));
    bufp->chgCData(oldp+139,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_level),5);
    bufp->chgBit(oldp+140,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_underflow));
    bufp->chgCData(oldp+141,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level),5);
    bufp->chgIData(oldp+142,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i),32);
    bufp->chgCData(oldp+143,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp),5);
    bufp->chgCData(oldp+144,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr),5);
    bufp->chgCData(oldp+145,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray),5);
    bufp->chgCData(oldp+146,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_ms),5);
    bufp->chgCData(oldp+147,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_rd),5);
    bufp->chgCData(oldp+148,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr),5);
    bufp->chgCData(oldp+149,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray),5);
    bufp->chgCData(oldp+150,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_ms),5);
    bufp->chgCData(oldp+151,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_wr),5);
    bufp->chgCData(oldp+152,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin),5);
    bufp->chgCData(oldp+153,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin),5);
    bufp->chgCData(oldp+154,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0]),8);
    bufp->chgCData(oldp+155,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[1]),8);
    bufp->chgCData(oldp+156,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[2]),8);
    bufp->chgCData(oldp+157,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[3]),8);
    bufp->chgCData(oldp+158,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[4]),8);
    bufp->chgCData(oldp+159,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[5]),8);
    bufp->chgCData(oldp+160,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[6]),8);
    bufp->chgCData(oldp+161,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[7]),8);
    bufp->chgCData(oldp+162,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[8]),8);
    bufp->chgCData(oldp+163,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[9]),8);
    bufp->chgCData(oldp+164,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[10]),8);
    bufp->chgCData(oldp+165,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[11]),8);
    bufp->chgCData(oldp+166,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[12]),8);
    bufp->chgCData(oldp+167,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[13]),8);
    bufp->chgCData(oldp+168,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[14]),8);
    bufp->chgCData(oldp+169,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[15]),8);
    bufp->chgIData(oldp+170,(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i),32);
    bufp->chgBit(oldp+171,(vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if.tready));
    bufp->chgBit(oldp+172,(vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if.tvalid));
}

void Vaxis_async_fifo_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vaxis_async_fifo_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxis_async_fifo_tb___024root*>(voidSelf);
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
