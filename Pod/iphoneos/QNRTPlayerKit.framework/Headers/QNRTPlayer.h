//
//  QNRTPlayer.h
//  QNRTPlayerKit
//
//  Created by 何云旗 on 2020/12/23.
//

#import <Foundation/Foundation.h>
#import "QNRTTypeDefines.h"

@class QNRTPlayer;
@class QNRTVideoView;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @protocol QNRTPlayerDelegate
 *
 * @discussion QNRTPlayer 在运行过程中的状态和事件回调。
 *
 * @since v1.0.0
 */
@protocol QNRTPlayerDelegate <NSObject>

@optional
/*!
 * @abstract SDK 运行过程中发生错误会通过该方法回调。
 *
 * @discussion 具体错误码的含义可以见 QNRTTypeDefines.h 文件。
 *
 * @since v1.0.0
 */
- (void)RTPlayer:(QNRTPlayer *)player didFailWithError:(NSError *)error;

/**
 * QNRTPlayer 在运行过程中，状态发生变化的回调
 *
 * @param player QNRTPlayer
 * @param playState 播放状态
 * @discussion QNRTPlayStateError 不会通过此回调，会通过 - (void)RTPlayer:(QNRTPlayer *)player didFailWithError:(NSError *)error;回调出来。
 *
 * @since v1.0.0
 */
- (void)RTPlayer:(QNRTPlayer *)player playStateDidChange:(QNRTPlayState)playState;

/*!
 * @abstract 统计信息回调。
 *
 * @discussion 回调的时间间隔由 statisticInterval 参数决定，statisticInterval 默认为 0，即不回调统计信息。
 *
 * @see statisticInterval
 *
 * @since v1.0.0
 */
- (void)RTPlayer:(QNRTPlayer *)player didGetStatistic:(NSDictionary *)statistic;

/*!
 * @abstract 当前流媒体流收到音频轨道。
 *
 * @since v1.0.0
 */
- (void)RTPlayer:(QNRTPlayer *)player trackDidReceived:(QNRTSourceKind )kind;

/*!
 * @abstract 音视频首帧解码后的回调。
 *
 * @since v1.0.0
 */
- (void)RTPlayer:(QNRTPlayer *)player firstSourceDidDecode:(QNRTSourceKind )kind;

@end

@interface QNRTPlayer : NSObject

/*!
 * @abstract 状态回调的 delegate。
 *
 * @since v1.0.0
 */
@property (nonatomic, weak) id<QNRTPlayerDelegate> delegate;

/*!
 * @abstract 播放状态
 *
 * @since v1.0.0
 */
@property (nonatomic, assign, readonly) QNRTPlayState playState;

/*!
 * @abstract 是否在播放
 *
 * @since v1.0.0
 */
@property (nonatomic, assign, readonly) BOOL isPlaying;

/*!
 * @abstract 播放 url
 *
 * @since v1.0.0
 */
@property (nonatomic, copy, readonly) NSURL *playUrl;

/*!
 * @abstract 播放音量。
 *
 * @discussion 范围从 0 ~ 1，默认为 1。
 *
 * @since v1.0.0
 */
@property (nonatomic, assign) double volume;

/**
 * 视频的宽
 *
 * @since v1.0.0
 */
@property (nonatomic, assign, readonly) CGFloat width;

/**
 * 视频的高
 *
 * @since v1.0.0
 */
@property (nonatomic, assign, readonly) CGFloat height;

/*!
 * @abstract 统计信息回调的时间间隔。
 *
 * @discussion 单位为秒。默认为 0，即默认不会回调统计信息。
 *
 * @since v1.0.0
 */
@property (nonatomic, assign) NSUInteger statisticInterval;

/*!
 * @abstract 渲染播放画面。
 *
 * @since v1.0.0
 */
@property (nonatomic, strong) QNRTVideoView *playView;

/**
 * 开始播放新的 url
 *
 * @param url 需要播放的 url ，目前支持 webrtc (url 以 webrtc:// 开头) 协议。
 * @param isSupport 当前播放 URL 是否支持 SSL 证书，默认为 NO
 *
 * @since v1.0.0
 */
- (void)playWithUrl:(NSURL *)url supportHttps:(BOOL)isSupport;

/**
 * 停止播放器
 *
 * @since v1.0.0
 */
- (void)stop;

/**
 * 静音
 *
 * @since 1.0.0
 */
- (void)muteAudio:(BOOL)mute;
/**
 * 停止画面渲染
 *
 * @since 1.0.0
 */
- (void)muteVideo:(BOOL)mute;

@end

#pragma mark - Category (Logging)

/*!
 * @category QNRTPlayer(Logging)
 *
 * @discussion 与日志相关的接口。
 *
 * @since v1.0.0
 */
@interface QNRTPlayer (Logging)

/*!
* @abstract 开启文件日志
*
* @discussion 为了不错过日志，建议在 App 启动时即开启，日志文件位于 App Container/Library/Caches/Pili/RTLogs 目录下以 QNRTPlayer+当前时间命名的目录内
* 注意：文件日志功能主要用于排查问题，打开文件日志功能会对性能有一定影响，上线前请记得关闭文件日志功能！
*
* @since v1.0.0
*/
+ (void)enableFileLogging;

@end

#pragma mark - Category (Info)

/*!
 * @category QNRTPlayer(Info)
 *
 * @discussion SDK 相关信息的接口。
 *
 * @since v1.0.0
 */
@interface QNRTPlayer (Info)

/*!
 * @abstract 获取 SDK 的版本信息。
 *
 * @since v1.0.0
 */
+ (NSString *)versionInfo;

@end

NS_ASSUME_NONNULL_END
