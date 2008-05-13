/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#include "Cookie.h"
#include "Util.h"
#include "A2STR.h"

namespace aria2 {

Cookie::Cookie(const std::string& name,
	       const std::string& value,
	       time_t  expires,
	       const std::string& path,
	       const std::string& domain,
	       bool secure):
  name(name),
  value(value),
  expires(expires),
  path(path),
  domain(domain),
  secure(secure),
  onetime(false) {}

Cookie::Cookie(const std::string& name,
	       const std::string& value,
	       const std::string& path,
	       const std::string& domain,
	       bool secure):
  name(name),
  value(value),
  path(path),
  domain(domain),
  secure(secure),
  onetime(true) {}

Cookie::Cookie():expires(0), secure(false), onetime(true) {}

Cookie::~Cookie() {}

std::string Cookie::toString() const
{
  return name+"="+value;
}

void Cookie::clear()
{
  name = value = path = domain = A2STR::NIL;
  expires = 0;
  secure = false;
}

bool Cookie::good() const
{
  return !name.empty();
}

bool Cookie::match(const std::string& host, const std::string& dir, time_t date, bool secure) const
{
  if((secure || (!this->secure && !secure)) &&
     Util::endsWith("."+host, this->domain) &&
     Util::startsWith(dir, this->path) &&
     (this->onetime || (date < this->expires))) {
    return true;
  } else {
    return false;
  }
}

} // namespace aria2
