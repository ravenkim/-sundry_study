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

package com.skydoves.allinone.factory

import android.content.Context
import android.graphics.Color
import android.view.Gravity
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import com.skydoves.allinone.R
import com.skydoves.powermenu.MenuAnimation
import com.skydoves.powermenu.PowerMenu
import com.skydoves.powermenu.PowerMenuItem

class WeatherMenuFactory : PowerMenu.Factory() {

  override fun create(context: Context, lifecycle: LifecycleOwner): PowerMenu {
    return PowerMenu.Builder(context)
      .addItem(PowerMenuItem(context.getString(R.string.label_settings), true))
      .addItem(PowerMenuItem(context.getString(R.string.label_change_location), false))
      .addItem(PowerMenuItem(context.getString(R.string.label_daily_alarm), false))
      .setLifecycleOwner(lifecycle)
      .setAnimation(MenuAnimation.SHOWUP_TOP_RIGHT)
      .setMenuRadius(13f)
      .setMenuShadow(10f)
      .setTextColor(Color.WHITE)
      .setTextGravity(Gravity.CENTER)
      .setMenuColor(ContextCompat.getColor(context, R.color.background800))
      .setSelectedTextColor(ContextCompat.getColor(context, R.color.white))
      .setSelectedMenuColor(ContextCompat.getColor(context, R.color.colorPrimaryDark))
      .setSelectedEffect(false)
      .setShowBackground(false)
      .build()
  }
}
