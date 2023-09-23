// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mprpcHeader.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_mprpcHeader_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_mprpcHeader_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_mprpcHeader_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_mprpcHeader_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mprpcHeader_2eproto;
namespace mprpcHeader {
class rpcHeader;
struct rpcHeaderDefaultTypeInternal;
extern rpcHeaderDefaultTypeInternal _rpcHeader_default_instance_;
}  // namespace mprpcHeader
PROTOBUF_NAMESPACE_OPEN
template<> ::mprpcHeader::rpcHeader* Arena::CreateMaybeMessage<::mprpcHeader::rpcHeader>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mprpcHeader {

// ===================================================================

class rpcHeader final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mprpcHeader.rpcHeader) */ {
 public:
  inline rpcHeader() : rpcHeader(nullptr) {}
  ~rpcHeader() override;
  explicit PROTOBUF_CONSTEXPR rpcHeader(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  rpcHeader(const rpcHeader& from);
  rpcHeader(rpcHeader&& from) noexcept
    : rpcHeader() {
    *this = ::std::move(from);
  }

  inline rpcHeader& operator=(const rpcHeader& from) {
    CopyFrom(from);
    return *this;
  }
  inline rpcHeader& operator=(rpcHeader&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const rpcHeader& default_instance() {
    return *internal_default_instance();
  }
  static inline const rpcHeader* internal_default_instance() {
    return reinterpret_cast<const rpcHeader*>(
               &_rpcHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(rpcHeader& a, rpcHeader& b) {
    a.Swap(&b);
  }
  inline void Swap(rpcHeader* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(rpcHeader* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  rpcHeader* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<rpcHeader>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const rpcHeader& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const rpcHeader& from) {
    rpcHeader::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(rpcHeader* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mprpcHeader.rpcHeader";
  }
  protected:
  explicit rpcHeader(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kServiceNameFieldNumber = 1,
    kMethodNameFieldNumber = 2,
    kArgsSizeFieldNumber = 3,
  };
  // string serviceName = 1;
  void clear_servicename();
  const std::string& servicename() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_servicename(ArgT0&& arg0, ArgT... args);
  std::string* mutable_servicename();
  PROTOBUF_NODISCARD std::string* release_servicename();
  void set_allocated_servicename(std::string* servicename);
  private:
  const std::string& _internal_servicename() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_servicename(const std::string& value);
  std::string* _internal_mutable_servicename();
  public:

  // string methodName = 2;
  void clear_methodname();
  const std::string& methodname() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_methodname(ArgT0&& arg0, ArgT... args);
  std::string* mutable_methodname();
  PROTOBUF_NODISCARD std::string* release_methodname();
  void set_allocated_methodname(std::string* methodname);
  private:
  const std::string& _internal_methodname() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_methodname(const std::string& value);
  std::string* _internal_mutable_methodname();
  public:

  // uint32 argsSize = 3;
  void clear_argssize();
  uint32_t argssize() const;
  void set_argssize(uint32_t value);
  private:
  uint32_t _internal_argssize() const;
  void _internal_set_argssize(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:mprpcHeader.rpcHeader)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr servicename_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr methodname_;
    uint32_t argssize_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_mprpcHeader_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// rpcHeader

// string serviceName = 1;
inline void rpcHeader::clear_servicename() {
  _impl_.servicename_.ClearToEmpty();
}
inline const std::string& rpcHeader::servicename() const {
  // @@protoc_insertion_point(field_get:mprpcHeader.rpcHeader.serviceName)
  return _internal_servicename();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void rpcHeader::set_servicename(ArgT0&& arg0, ArgT... args) {
 
 _impl_.servicename_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mprpcHeader.rpcHeader.serviceName)
}
inline std::string* rpcHeader::mutable_servicename() {
  std::string* _s = _internal_mutable_servicename();
  // @@protoc_insertion_point(field_mutable:mprpcHeader.rpcHeader.serviceName)
  return _s;
}
inline const std::string& rpcHeader::_internal_servicename() const {
  return _impl_.servicename_.Get();
}
inline void rpcHeader::_internal_set_servicename(const std::string& value) {
  
  _impl_.servicename_.Set(value, GetArenaForAllocation());
}
inline std::string* rpcHeader::_internal_mutable_servicename() {
  
  return _impl_.servicename_.Mutable(GetArenaForAllocation());
}
inline std::string* rpcHeader::release_servicename() {
  // @@protoc_insertion_point(field_release:mprpcHeader.rpcHeader.serviceName)
  return _impl_.servicename_.Release();
}
inline void rpcHeader::set_allocated_servicename(std::string* servicename) {
  if (servicename != nullptr) {
    
  } else {
    
  }
  _impl_.servicename_.SetAllocated(servicename, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.servicename_.IsDefault()) {
    _impl_.servicename_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mprpcHeader.rpcHeader.serviceName)
}

// string methodName = 2;
inline void rpcHeader::clear_methodname() {
  _impl_.methodname_.ClearToEmpty();
}
inline const std::string& rpcHeader::methodname() const {
  // @@protoc_insertion_point(field_get:mprpcHeader.rpcHeader.methodName)
  return _internal_methodname();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void rpcHeader::set_methodname(ArgT0&& arg0, ArgT... args) {
 
 _impl_.methodname_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:mprpcHeader.rpcHeader.methodName)
}
inline std::string* rpcHeader::mutable_methodname() {
  std::string* _s = _internal_mutable_methodname();
  // @@protoc_insertion_point(field_mutable:mprpcHeader.rpcHeader.methodName)
  return _s;
}
inline const std::string& rpcHeader::_internal_methodname() const {
  return _impl_.methodname_.Get();
}
inline void rpcHeader::_internal_set_methodname(const std::string& value) {
  
  _impl_.methodname_.Set(value, GetArenaForAllocation());
}
inline std::string* rpcHeader::_internal_mutable_methodname() {
  
  return _impl_.methodname_.Mutable(GetArenaForAllocation());
}
inline std::string* rpcHeader::release_methodname() {
  // @@protoc_insertion_point(field_release:mprpcHeader.rpcHeader.methodName)
  return _impl_.methodname_.Release();
}
inline void rpcHeader::set_allocated_methodname(std::string* methodname) {
  if (methodname != nullptr) {
    
  } else {
    
  }
  _impl_.methodname_.SetAllocated(methodname, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.methodname_.IsDefault()) {
    _impl_.methodname_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:mprpcHeader.rpcHeader.methodName)
}

// uint32 argsSize = 3;
inline void rpcHeader::clear_argssize() {
  _impl_.argssize_ = 0u;
}
inline uint32_t rpcHeader::_internal_argssize() const {
  return _impl_.argssize_;
}
inline uint32_t rpcHeader::argssize() const {
  // @@protoc_insertion_point(field_get:mprpcHeader.rpcHeader.argsSize)
  return _internal_argssize();
}
inline void rpcHeader::_internal_set_argssize(uint32_t value) {
  
  _impl_.argssize_ = value;
}
inline void rpcHeader::set_argssize(uint32_t value) {
  _internal_set_argssize(value);
  // @@protoc_insertion_point(field_set:mprpcHeader.rpcHeader.argsSize)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace mprpcHeader

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_mprpcHeader_2eproto
