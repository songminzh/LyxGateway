//
//  LyxGatewayResult.h
//  LyxGateway
//
//  Created by zheng on 2023/2/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LyxGatewayResult : NSObject

/// 返回码枚举
typedef NS_ENUM(NSInteger, LyxGatewayResultCode) {
    LyxGatewayResultAntiAddictioExceedTheTimeOfDay = -12, // 未成年人玩游戏超过规定时间
    LyxGatewayResultAntiAddictioNonAllowedTime = -11, // 未成年人须在规定时间段玩游戏
    LyxGatewayResultAntiAddictionWeekend = -10, // 未成年人非节假日或周末不可玩游戏
    LyxGatewayResultError = -1, // 失败（服务器返回）
    LyxGatewayResultSuccess = 0, // 成功
    LyxGatewayResultSignInAccountNotPhoneNumer = 1, // 注册时使用非手机号作为注册账号
    LyxGatewayResultNetworkError = 2, // 网络请求错误
    LyxGatewayResultPhoneNumberInexistence = 3, // 手机号不存在
    LyxGatewayResultIdNumberInexistence = 4, // 身份证号不存在
    LyxGatewayResultPasswordUnqualified = 5, // 密码不符合要求
    LyxGatewayResultUserCanceled = 6, // 用户取消
    LyxGatewayResultLackOfRequiredParameters = 7, // 缺少必要参数
};

/// 返回码
@property (nonatomic, assign) LyxGatewayResultCode code;
/// 返回信息描述
@property (nonatomic, copy) NSString * message;
/// 返回数据（根据不同接口返回不同数据模型）
@property (nonatomic, strong) id data;

@end


/// 登录返回数据模型
@interface LyxGatewayLoginData : NSObject

/// 是否为新注册用户；true 是，false 不是
@property (nonatomic, assign) BOOL isReg;
/// 用户的全平台唯一ID
@property (nonatomic, copy) NSString * platId;
/// 用户在该商户下的唯一ID
@property (nonatomic, copy) NSString * unionId;
/// 用户在该商户的应用下的唯一ID
@property (nonatomic, copy) NSString * openId;
/// jwt的token，后续接口需要将token放在请求头【Authorization】中
@property (nonatomic, copy) NSString * token;

@end


/// 防沉迷数据模型
@interface LyxGatewayAntiAddictionInfo : NSObject

/// 返回码
@property (nonatomic, assign) LyxGatewayResultCode code;
/// 返回信息描述
@property (nonatomic, copy) NSString * message;
/// 今日游戏时长
@property (nonatomic, assign) NSUInteger todayPlayTime;

@end


/// 用户信息模型
@interface LyxGatewayUserInfo : NSObject
/// 昵称
@property (nonatomic, copy) NSString * nick;
/// 头像url地址
@property (nonatomic, copy) NSString * avatar;
/// 手机号
@property (nonatomic, copy) NSString * tel;
/// 注册时间；时间戳
@property (nonatomic, copy) NSNumber * regTime;
/// 登录时间；时间戳
@property (nonatomic, copy) NSNumber * loginTime;
/// 上次登录时间；时间戳
@property (nonatomic, copy) NSNumber * lastLoginTime;
/// 登录IP
@property (nonatomic, copy) NSString * loginIp;
/// 用户年龄
@property (nonatomic, copy) NSNumber * age;
/// 身份证信息
@property (nonatomic, copy) NSString * card;
/// 姓名
@property (nonatomic, copy) NSString * name;

@end


/// 实名认证模型
@interface LyxGatewayUserVerificationStatus : NSObject
/// 用户年龄
@property (nonatomic, assign) int age;
/// 实名状态；true：已实名，false：未实名
@property (nonatomic, assign) BOOL status;
/// 需要满足年龄
@property (nonatomic, assign) int requireAge;

@end

/// 初始化配置模型
@interface LyxGatewayConfig : NSObject
/// 是否开启在线时长限制（防沉迷） 0关 1开
@property (nonatomic, assign) NSInteger online_limit;
/// 是否需要实名 0关 1开
@property (nonatomic, assign) NSInteger app_verified;
/// 充值配置
@property (nonatomic, strong) NSArray * recharge;
/// 支付方式 英文逗号隔开 多选 1,2,3 (1=支付宝,2=微信,3=微信小程序)
@property (nonatomic, copy) NSString * app_pay_way;

@end


/// 订单模型
@interface LyxGatewayOrder : NSObject

/// 支付类型选择【必传】
/// 取值：
/// alipay_h5【支付宝H5】
/// alipay_pc【支付宝网页扫码】
/// wechat_h5【微信H5】
/// wechat_native【微信扫码】
/// wechat_jsapi【微信JSAPI】
@property (nonatomic, copy) NSString * payMethod;

/// 商户订单号【必传】
@property (nonatomic, copy) NSString * mchOrderId;

/// 商品ID【必传】
@property (nonatomic, copy) NSString * goodsId;

/// 商品数量【必传】
@property (nonatomic, assign) NSInteger goodsNum;

/// 商品标题/商品名称【必传】
@property (nonatomic, copy) NSString * goodsTitle;

/// 商品总价，单位：分【必传】
@property (nonatomic, assign) NSInteger totalPrice;

/// 商户ID【必传】
@property (nonatomic, assign) NSInteger mchId;

/// 应用ID【必传】
@property (nonatomic, assign) NSInteger * appId;

/// 用户ID类型，取值：unionId，openId，platId；也就是说这三个id必须传入一个【必传】
@property (nonatomic, copy) NSString * idType;

/// 用户unionId【非必传】
@property (nonatomic, copy) NSString * unionId;

/// 用户openid【非必传】
@property (nonatomic, copy) NSString * openid;

/// 用户platId【非必传】
@property (nonatomic, copy) NSString * platId;

/// 支付成功的回跳url地址【非必传】
@property (nonatomic, copy) NSString * returnUrl;

/// 选择微信jsapi支付方式时，必须传入【非必传】
@property (nonatomic, copy) NSString * wxOpenId;

/// 下单时间【非必传】
@property (nonatomic, assign) NSInteger orderTime;

/// 支付宝PC扫码支付二维码链接模式，默认为 0 ；0：爬取支付宝的二维码；1：pc扫码原链接【非必传】
@property (nonatomic, assign) NSInteger alipayPcLinkType;

@end

NS_ASSUME_NONNULL_END
