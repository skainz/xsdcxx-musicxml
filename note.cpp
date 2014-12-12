#include "musicxml.hpp"

#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace musicxml {

note::note(const pitch_type &pitch, const duration_type &duration)
: note_base{} {
  this->pitch(pitch);
  this->duration(duration);
}

note::note(const unpitched_type &unpitched, const duration_type &duration)
: note_base{} {
  this->unpitched(unpitched);
  this->duration(duration);
}

note::note(const rest_type &rest, const duration_type &duration) : note_base{} {
  this->rest(rest);
  this->duration(duration);
}

note::note(const note &x, ::xml_schema::flags f, ::xml_schema::container *c)
: note_base{x, f, c} {}

note::note(const ::xercesc::DOMElement &e, ::xml_schema::flags f,
           ::xml_schema::container *c)
: note_base{e, f, c} {}

void note::grace(const grace_type &x) {
  this->duration().reset();
  note_base::grace(x);
}

void note::grace(const grace_optional &x) {
  if (x) this->duration().reset();
  note_base::grace(x);
}

void note::grace(::std::unique_ptr<grace_type> p) {
  if (p) this->duration().reset();
  note_base::grace(std::move(p));
}

note *note::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class note(*this, f, c);
}

// The automatically generated serialization code will occasionally generate
// documents that are invalid according to the schema.  The serialization order
// produced by xsdcxx 4.0.0 needs to be adjusted a bit.
void operator<<(::xercesc::DOMElement &e, const note &i) {
  e << static_cast<const ::xml_schema::type &>(i);

  using ::xsd::cxx::xml::dom::create_element;
  using ::xsd::cxx::xml::dom::create_attribute;

  if (i.grace())
    create_element("grace", e) << *i.grace();
  else if (i.cue())
    create_element("cue", e) << *i.cue();

  if (i.chord()) create_element("chord", e) << *i.chord();

  if (i.pitch())
    create_element("pitch", e) << *i.pitch();
  else if (i.unpitched())
    create_element("unpitched", e) << *i.unpitched();
  else if (i.rest())
    create_element("rest", e) << *i.rest();

  if (!i.grace().present() && i.duration())
    create_element("duration", e) << *i.duration();

  if (!i.cue().present())
    for (const auto &elem : i.tie()) create_element("tie", e) << elem;

  if (i.instrument()) create_element("instrument", e) << *i.instrument();
  if (i.footnote()) create_element("footnote", e) << *i.footnote();
  if (i.level()) create_element("level", e) << *i.level();
  if (i.voice()) create_element("voice", e) << *i.voice();
  if (i.type()) create_element("type", e) << *i.type();
  for (const auto &elem : i.dot()) create_element("dot", e) << elem;
  if (i.accidental()) create_element("accidental", e) << *i.accidental();
  if (i.time_modification())
    create_element("time-modification", e) << *i.time_modification();
  if (i.stem()) create_element("stem", e) << *i.stem();
  if (i.notehead()) create_element("notehead", e) << *i.notehead();
  if (i.notehead_text())
    create_element("notehead-text", e) << *i.notehead_text();
  if (i.staff()) create_element("staff", e) << *i.staff();
  for (const auto &elem : i.beam()) create_element("beam", e) << elem;
  for (const auto &elem : i.notations()) create_element("notations", e) << elem;
  for (const auto &elem : i.lyric()) create_element("lyric", e) << elem;
  if (i.play()) create_element("play", e) << *i.play();

  if (i.default_x()) create_attribute("default-x", e) << *i.default_x();
  if (i.default_y()) create_attribute("default-y", e) << *i.default_y();
  if (i.relative_x()) create_attribute("relative-x", e) << *i.relative_x();
  if (i.relative_y()) create_attribute("relative-y", e) << *i.relative_y();
  if (i.font_family()) create_attribute("font-family", e) << *i.font_family();
  if (i.font_style()) create_attribute("font-style", e) << *i.font_style();
  if (i.font_size()) create_attribute("font-size", e) << *i.font_size();
  if (i.font_weight()) create_attribute("font-weight", e) << *i.font_weight();
  if (i.color()) create_attribute("color", e) << *i.color();
  if (i.print_object())
    create_attribute("print-object", e) << *i.print_object();
  if (i.print_dot()) create_attribute("print-dot", e) << *i.print_dot();
  if (i.print_spacing())
    create_attribute("print-spacing", e) << *i.print_spacing();
  if (i.print_lyric()) create_attribute("print-lyric", e) << *i.print_lyric();
  if (i.dynamics()) create_attribute("dynamics", e) << *i.dynamics();
  if (i.end_dynamics())
    create_attribute("end-dynamics", e) << *i.end_dynamics();
  if (i.attack()) create_attribute("attack", e) << *i.attack();
  if (i.release()) create_attribute("release", e) << *i.release();
  if (i.time_only()) create_attribute("time-only", e) << *i.time_only();
  if (i.pizzicato()) create_attribute("pizzicato", e) << *i.pizzicato();
}

} // namespace musicxml
