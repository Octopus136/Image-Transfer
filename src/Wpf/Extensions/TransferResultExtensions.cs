using BridgeTransferResult = ImageTransfer.Bridge.TransferResult;

public static class BridgeTransferResultExtensions
{
    public static string GetResourceKey(this BridgeTransferResult result) =>
        result switch
        {
            BridgeTransferResult.ErrParams => "ReasonParams",
            BridgeTransferResult.ErrSize => "ReasonSize",
            BridgeTransferResult.ErrCodecs => "ReasonCodecs",
            BridgeTransferResult.ErrUnknown => "ReasonUnknown",
            _ => "ReasonUnknown"
        };
}
