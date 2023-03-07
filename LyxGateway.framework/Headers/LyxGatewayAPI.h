//
//  LyxGatewayAPI.h
//  LyxGateway
//
//  Created by zheng on 2023/2/14.
//

#import <Foundation/Foundation.h>
#import "LyxGatewayResult.h"

NS_ASSUME_NONNULL_BEGIN

@protocol LyxLyxGatewayDelegate <NSObject>

@optional
/// 防沉迷监听
/// @param info 返回防沉迷数据，LyxGatewayAntiAddictionInfo类（ 每五分钟返回一次）
- (void)lyx_antiAddictionInfo:(LyxGatewayAntiAddictionInfo *)info;

@end

@interface LyxGatewayAPI : NSObject

/// 初始化
/// - Parameters:
///   - mchId: 商户ID【必传】
///   - appId: 应用ID【必传】
///   - delegate: LyxLyxGatewayDelegate
/// - Return: 初始化结果
+ (BOOL)initWithMchId:(int)mchId appId:(int)appId delegate:(nullable id<LyxLyxGatewayDelegate>)delegate;

/// 登录
/// - Parameter result: 结果回调 LyxGatewayResult类
+ (void)login:(void (^)(LyxGatewayResult * res))result;

/// 获取短信验证码
/// 接口限制每日每个用户限用10次，超过限制后将不会再进行短信发送
/// - Parameters:
///   - tel: 手机号（11位手机号）【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)sendSmsCodeWithTel:(NSString *)tel result:(void (^)(LyxGatewayResult *res))result;

/// 获取短信验证码【已登录状态下】
/// 获取验证码用于修改用户信息、修改密码等操作
/// 接口限制每日每个用户限用10次，超过限制后将不会再进行短信发送
/// - Parameters:
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)sendSmsCodeWithToken:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 手机号登录【商户应用调用】
/// 商户下的应用请使用该接口进行用户登录
/// 登录成功后会获取两个ID；其中unionId表示该商户下唯一，openId表示该应用下唯一。（说明：unionId，一个用户在一个商户下所有应用都是同一个，openId，一个用户在一个应用中是同一个，不同应用中是不同的）
/// 登录时，短信验证码和密码必须传一个
/// - Parameters:
///   - mchId: 商户ID【必传】
///   - appId: 应用ID【必传】
///   - tel: 手机号【必传】
///   - telCode: 短信验证码【非必传】
///   - password: 密码【非必传】
///   - result: 结果回调 LyxGatewayResult类（该接口LyxGatewayResult.data返回LyxGatewayLoginData模型数据）
+ (void)loginWithMchId:(int)mchId appId:(int)appId tel:(NSString *)tel telCode:(NSString *)telCode password:(NSString *)password result:(void (^)(LyxGatewayResult *res))result;

/// 实名认证
/// - Parameters:
///   - name: 姓名【必传】
///   - idNum: 身份证号【必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)identityVerificationWithName:(NSString *)name idNum:(NSString *)idNum token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 获取用户实名状态
/// - Parameters:
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)getIdentityVerificationStatusWithToken:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;


/// 获取防沉迷数据
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayAntiAddictionInfo类
+ (void)getAntiAddictionInfoWithToken:(NSString *)token result:(void (^)(LyxGatewayAntiAddictionInfo * info))result;

/// 充值下单
/// - Parameters:
///   - order: LyxGatewayOrder类【必传】
///   - token: 登录返回的token 【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)addOrder:(LyxGatewayOrder *)order token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 获取微信openId
/// 使用微信JSAPI支付方式需要获取用户的微信openid时，请调用该接口获取
/// 调用接口需要先获取用户授权code。此处采用静默授权即可（即：scope = snsapi_base）
/// 参考微信文档：https://developers.weixin.qq.com/doc/offiaccount/OA_Web_Apps/Wechat_webpage_authorization.html
/// - Parameters:
///   - wxCode: 用户授权code【必传】
///   - wxAppId: 指定微信appid【非必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)getWechatOpenIdWithWxCode:(NSString *)wxCode wxAppId:(NSString *)wxAppId token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 设置密码 / 修改密码
/// - Parameters:
///   - password: 密码；密码需要长度6~32位，包含字母和数字【必传】
///   - telCode: 短信验证码【必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)setPassword:(NSString *)password telCode:(NSString *)telCode token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 获取用户微信个人信息
/// 用户授权获取用户微信信息；
/// 注意：授权时，scope = snsapi_userinfo
/// 默认微信AppId = wxf1e3bded5748b1dc
/// 返回结果参考微信接口返回：https://developers.weixin.qq.com/doc/offiaccount/OA_Web_Apps/Wechat_webpage_authorization.html#3
/// - Parameters:
///   - wxAuthCode: 微信授权用户code【必传】
///   - wxAppId: 微信公众号配置【非必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)getUserInfoFromWechat:(NSString *)wxAuthCode wxAppId:(NSString *)wxAppId token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 绑定微信
/// - Parameters:
///   - wxAuthCode: 微信授权用户code【必传】
///   - changeBind: 是否更换绑定，默认值：1；此参数，在更换绑定时传入【非必传】
///   - telCode: 短信验证码，更换绑定时需要传入【非必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)bindWechat:(NSString *)wxAuthCode changeBind:(NSInteger)changeBind telCode:(NSString *)telCode token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 绑定手机号
/// - Parameters:
///   - tel: 手机号【必传】
///   - telCode: 短信验证码【必传】
///   - changeBind: 是否更换绑定，默认值：1；此参数，在更换绑定时传入【非必传】
///   - oldTel: 原手机号，在更换绑定时传入【非必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类（该接口LyxGatewayResult.data返回LyxGatewayUserInfo模型数据）
+ (void)bindTel:(NSString *)tel telCode:(NSString *)telCode changeBind:(NSInteger)changeBind  oldTel:(NSString *)oldTel token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 获取用户信息
/// - Parameters:
///   - platId: 平台ID【非必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)getUserInfoByPlatId:(nullable NSString *)platId token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

/// 修改昵称或头像
/// - Parameters:
///   - nickname: 用户昵称【非必传  】
///   - avatar: 用户头像URL【非必传】
///   - platId: 用户platId【非必传】
///   - token: 登录返回的token【必传】
///   - result: 结果回调 LyxGatewayResult类
+ (void)alterNickname:(nullable NSString *)nickname avatar:(nullable NSString *)avatar platId:(nullable NSString *)platId token:(NSString *)token result:(void (^)(LyxGatewayResult *res))result;

@end

NS_ASSUME_NONNULL_END
