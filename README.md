# SnifferIH

Injectable DLL that captures any traffic made by the application it has been injected to.

The traffic captured gets wrote in files inside the Send and Recv directories created by the DLL.


## Details

The DLL uses hooking on the process it gets injected in, which is implemented on the `ws2_32.dll` `send` and `recv` in order to capture every packet sent and received.

`ws2_32.dll` is the main DLL any recent Windows OS uses in order to transmit data over any protocol.
Since this DLL is the main public "gate" user mode applications use to ask the kernel to transmit data, it doesn't matter what kind of networking library the target executable uses, since the request will always end up in those hooked points.

While it's true that an application can use the older networking API (`ws2_32.dll`) which Windows provides for retro compatibility, on newer OSes it just ends up calling the new API, so the DLL will cover it aswell.


## TODO

Add some other protocol functions such as WSASend and WSARecv and possibly sniffing on some connecting and binding ones.

You can however modify the DLL source code yourself, including new functions or changing the code applied on the hooks trampolines set up already.
