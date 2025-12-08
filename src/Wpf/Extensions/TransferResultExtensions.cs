using BridgeConvertResult = ImgSizer.Bridge.ConvertResult;

public static class BridgeConvertResultExtensions
{
    public static string GetResourceKey(this BridgeConvertResult result) =>
        result switch
        {
            BridgeConvertResult.ErrParams => "ReasonParams",
            BridgeConvertResult.ErrSize => "ReasonSize",
            BridgeConvertResult.ErrCodecs => "ReasonCodecs",
            BridgeConvertResult.ErrUnknown => "ReasonUnknown",
            _ => "ReasonUnknown"
        };
}
