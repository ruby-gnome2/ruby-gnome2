# Copyright (C) 2015  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 
class TestRegex < Test::Unit::TestCase

  def test_regex_enum_compile_flags
    assert_const_defined(GLib, :RegexCompileFlags)
    assert_kind_of(GLib::RegexCompileFlags, GLib::RegexCompileFlags::CASELESS)
  end

  def test_regex_enum_match_flags
    assert_const_defined(GLib, :RegexMatchFlags)
    assert_kind_of(GLib::RegexMatchFlags, GLib::RegexMatchFlags::PARTIAL_HARD)
  end

  def test_regex_new
    a_regex = GLib::Regex.new("to??", 0, 0)
    assert_instance_of(GLib::Regex, a_regex)
  end

  def test_regex_pattern
    a_regex = GLib::Regex.new("to??", 0, 0)
    assert_equal(a_regex.pattern, "to??")
  end

  def test_regex_compile_flags
    flags = GLib::RegexCompileFlags::CASELESS
    a_regex = GLib::Regex.new("to??", flags, 0)
    assert_equal(a_regex.compile_flags, flags) 
  end

  def test_regex_match_flags
    flags = GLib::RegexMatchFlags::PARTIAL_HARD
    a_regex = GLib::Regex.new("to??", 0, flags)
    assert_equal(a_regex.match_flags, flags) 
  end

  sub_test_case "max_backref" do
    test "none" do
      a_regex = GLib::Regex.new("to?o", 0, 0)
      assert_equal(a_regex.max_backref, 0)
    end
    test "one" do
      a_regex = GLib::Regex.new("(to(?)o)\\g1", 0, 0)
      assert_equal(a_regex.max_backref, 1)
    end
  end

  sub_test_case "match_simple" do
    test "true" do
      matched = GLib::Regex.match_simple("to", "tatota", 0, 0)
      assert(matched)
    end
    test "false" do
      matched = GLib::Regex.match_simple("ti", "tatota", 0, 0)
      assert_equal(matched, false)
    end
  end

  sub_test_case "capture_count" do
    test "none" do
      a_regex = GLib::Regex.new("to?o", 0, 0)
      assert_equal(a_regex.capture_count, 0)
    end
    test "one" do
      a_regex = GLib::Regex.new("(to(\?)o)", 0, 0)
      assert_equal(a_regex.capture_count, 1)
    end
    test "three" do
      a_regex = GLib::Regex.new("((red|white) (king|queen))", 0, 0)
      assert_equal(a_regex.capture_count, 3)
    end
  end

  sub_test_case "has_cr_or_lf" do
    test "none" do
      a_regex = GLib::Regex.new("to?o", 0, 0)
      assert_equal(a_regex.has_cr_or_lf, false)
    end
    test "both" do
      a_regex = GLib::Regex.new("to\no", 0, 0)
      assert(a_regex.has_cr_or_lf)
    end
    test "cr" do
      a_regex = GLib::Regex.new("to\rtiti", 0, 0)
      assert(a_regex.has_cr_or_lf)
    end
  end
end
