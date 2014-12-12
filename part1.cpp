#include "musicxml.hpp"
#include <xsd/cxx/xml/dom/serialization-source.hxx>
#include "music_data_serialization_visitor.hpp"
#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace musicxml {

const part1::id_type &part1::id() const { return this->id_.get(); }

part1::id_type &part1::id() { return this->id_.get(); }

void part1::id(const id_type &x) { this->id_.set(x); }

void part1::id(::std::unique_ptr<id_type> x) { this->id_.set(std::move(x)); }

const part1::music_data_sequence &part1::music_data() const {
  return this->music_data_;
}

part1::music_data_sequence &part1::music_data() { return this->music_data_; }

void part1::music_data(const music_data_sequence &s) { this->music_data_ = s; }

part1::part1(const id_type &id) : ::xml_schema::type(), id_(id, this) {}

part1::part1(const part1 &x, ::xml_schema::flags f, ::xml_schema::container *c)
: ::xml_schema::type(x, f, c)
, music_data_(x.music_data_)
, id_(x.id_, f, this) {}

part1::part1(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
             ::xml_schema::container *c)
: ::xml_schema::type(e, f | ::xml_schema::flags::base, c), id_(this) {
  if ((f & ::xml_schema::flags::base) == 0) {
    ::xsd::cxx::xml::dom::parser<char> p(e, true, false, true);
    this->parse(p, f);
  }
}

void part1::parse(::xsd::cxx::xml::dom::parser<char> &p,
                  ::xml_schema::flags f) {
  for (; p.more_content(); p.next_content(false)) {
    const ::xercesc::DOMElement &i(p.cur_element());
    const ::xsd::cxx::xml::qualified_name<char> n(
      ::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "note" && n.namespace_().empty()) {
      this->music_data_.push_back(note_type(i, f, this));
    } else if (n.name() == "backup" && n.namespace_().empty()) {
      this->music_data_.push_back(backup_type(i, f, this));
    } else if (n.name() == "forward" && n.namespace_().empty()) {
      this->music_data_.push_back(forward_type(i, f, this));
    } else if (n.name() == "direction" && n.namespace_().empty()) {
      this->music_data_.push_back(direction_type(i, f, this));
    } else if (n.name() == "attributes" && n.namespace_().empty()) {
      this->music_data_.push_back(attributes_type(i, f, this));
    } else if (n.name() == "harmony" && n.namespace_().empty()) {
      this->music_data_.push_back(harmony_type(i, f, this));
    } else if (n.name() == "figured-bass" && n.namespace_().empty()) {
      this->music_data_.push_back(figured_bass_type(i, f, this));
    } else if (n.name() == "print" && n.namespace_().empty()) {
      this->music_data_.push_back(print_type(i, f, this));
    } else if (n.name() == "sound" && n.namespace_().empty()) {
      this->music_data_.push_back(sound_type(i, f, this));
    } else if (n.name() == "barline" && n.namespace_().empty()) {
      this->music_data_.push_back(barline_type(i, f, this));
    } else if (n.name() == "grouping" && n.namespace_().empty()) {
      this->music_data_.push_back(grouping_type(i, f, this));
    } else if (n.name() == "link" && n.namespace_().empty()) {
      this->music_data_.push_back(link_type(i, f, this));
    } else if (n.name() == "bookmark" && n.namespace_().empty()) {
      this->music_data_.push_back(bookmark_type(i, f, this));
    } else { break; }
  }

  while (p.more_attributes()) {
    const ::xercesc::DOMAttr &i(p.next_attribute());
    const ::xsd::cxx::xml::qualified_name<char> n(
      ::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "id" && n.namespace_().empty()) {
      this->id_.set(id_traits::create(i, f, this));
      continue;
    }
  }

  if (!id_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("id", "");
  }
}

part1 *part1::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class part1(*this, f, c);
}

part1 &part1::operator=(const part1 &x) {
  if (this != &x) {
    static_cast<::xml_schema::type &>(*this) = x;
    this->music_data_ = x.music_data_;
    this->id_ = x.id_;
  }

  return *this;
}

part1::~part1() {}

void operator<<(::xercesc::DOMElement &e, const part1 &i) {
  e << static_cast<const ::xml_schema::type &>(i);

  serialization_visitor v(e);
  std::for_each(i.music_data().begin(), i.music_data().end(),
                boost::apply_visitor(v));

  ::xsd::cxx::xml::dom::create_attribute("id", e) << i.id();
}

} // namespace musicxml
