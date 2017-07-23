# SnifferIH

Injectable DLL that captures any traffic made by the application it has been injected to.

The traffic captured gets wrote in files inside the Send and Recv directories created by the DLL.

Hooking is implemented on the `ws2_32.dll` in order to capture every packet sent and received.
