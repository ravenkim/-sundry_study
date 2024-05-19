/*
 * Copyright (C) 2019 skydoves
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.skydoves.allinone.di

import androidx.annotation.NonNull
import com.skydoves.allinone.api.GoKrRequestInterceptor
import com.skydoves.allinone.api.KMARequestInterceptor
import com.skydoves.allinone.api.LiveDataCallAdapterFactory
import com.skydoves.allinone.api.client.GoKrClient
import com.skydoves.allinone.api.client.KMAClient
import com.skydoves.allinone.api.service.GoKrService
import com.skydoves.allinone.api.service.KMAService
import dagger.Module
import dagger.Provides
import okhttp3.OkHttpClient
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.converter.simplexml.SimpleXmlConverterFactory
import javax.inject.Named
import javax.inject.Singleton

@Suppress("SpellCheckingInspection")
@Module
class NetworkModule {

  @Provides
  @Singleton
  @Named("KMA")
  fun provideHttpClient(): OkHttpClient {
    return OkHttpClient.Builder()
        .addInterceptor(KMARequestInterceptor())
        .build()
  }

  @Provides
  @Singleton
  @Named("GOKR")
  fun provideGOKRHttpClient(): OkHttpClient {
    return OkHttpClient.Builder()
        .addInterceptor(GoKrRequestInterceptor())
        .build()
  }

  @Provides
  @Singleton
  @Named("KMA")
  fun provideKAMRetrofit(@NonNull @Named("KMA") okHttpClient: OkHttpClient): Retrofit {
    return Retrofit.Builder()
        .client(okHttpClient)
        .baseUrl("http://www.kma.go.kr/")
        .addConverterFactory(SimpleXmlConverterFactory.create())
        .addCallAdapterFactory(LiveDataCallAdapterFactory())
        .build()
  }

  @Provides
  @Singleton
  @Named("GOKR")
  fun provideGOKRRetrofit(@NonNull @Named("GOKR") okHttpClient: OkHttpClient): Retrofit {
    return Retrofit.Builder()
        .client(okHttpClient)
        .baseUrl("http://openapi.airkorea.or.kr/")
        .addConverterFactory(GsonConverterFactory.create())
        .addCallAdapterFactory(LiveDataCallAdapterFactory())
        .build()
  }

  @Provides
  @Singleton
  fun provideKMAService(@NonNull @Named("KMA") retrofit: Retrofit): KMAService {
    return retrofit.create(KMAService::class.java)
  }

  @Provides
  @Singleton
  fun provideKMAClient(@NonNull kmaService: KMAService): KMAClient {
    return KMAClient(kmaService)
  }

  @Provides
  @Singleton
  fun provideGoKRService(@NonNull @Named("GOKR") retrofit: Retrofit): GoKrService {
    return retrofit.create(GoKrService::class.java)
  }

  @Provides
  @Singleton
  fun provideGoKrClient(@NonNull goKrService: GoKrService): GoKrClient {
    return GoKrClient(goKrService)
  }
}
