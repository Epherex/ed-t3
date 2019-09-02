tad_name = ''
attributes = []

class Variable
    
    def initialize(type, name, required, size = nil)
        @type = type
        @name = name
        @required = required
        @size = size
    end

    def required
        @required
    end

    def name
        @name
    end

    def size
        return @size
    end

    def type
        return @type
    end

    def preffix
        if @size != nil 
            '*' 
        else 
            '' 
        end
    end

    def capital_name
        temp = @name.clone
        puts self.inspect
        temp[0] = @name[0].capitalize
        return temp
    end

    def full_name
        @type + ' ' + @name + (@size != nil ? '[]' : '')
    end

    def name_with_size
        @type + ' ' + @name + (@size != nil ? '[%d]' % [@size] : '')
    end
end

File.readlines('input.txt').each.with_index do |line, i|
    if i == 0
        tad_name = line.strip
    else
        match = /([^\*.]+)\[(\d+)\] (.+)$/.match(line)
        if match
            attributes.push(Variable.new(match[1], match[3], !line.strip.start_with?('*'), match[2]))
        else
            match = /([^\*.]+) (.+)$/.match(line)
            attributes.push(Variable.new(match[1], match[2], !line.strip.start_with?('*'))) if match
        end
    end
end

downcase_tad_name = tad_name[0].downcase + tad_name[1, tad_name.length - 1]
void = tad_name + ' ' + downcase_tad_name + 'Void'

getters = []
setters = []

h = attributes.select {|item| item.required}.map {|item| item.full_name}
creator = '%s %s_Create(%s)' % [tad_name, tad_name, h.join(', ')]

attributes.each do |at|
    getter = '%s %s%s_Get%s(%s)' % [at.type, at.preffix, tad_name, at.capital_name, void]
    getters.push(getter)
    setter = 'void %s_Set%s(%s)' % [tad_name, at.capital_name, void + ', ' + at.full_name]
    setters.push(setter)
end


headers = File.new(tad_name.downcase + '.h', 'w')
headers.puts('#ifndef %s_H' % [tad_name.upcase])
headers.puts('#define %s_H' % [tad_name.upcase])
headers.puts('')
headers.puts('typedef void *%s;' % [tad_name])
headers.puts('')
headers.puts(creator + ';')
headers.puts('')
getters.each do |f|
    headers.puts(f + ';')
    headers.puts('')
end
setters.each do |f|
    headers.puts(f + ';')
    headers.puts('')
end
headers.puts('#endif')
headers.close

source = File.new(tad_name.downcase + '.c', 'w')
source.puts('#include "%s.h"' % [tad_name.downcase])
source.puts('')
source.puts('typedef struct %s_t {' % [downcase_tad_name])
attributes.each do |at|
    source.puts('    %s;' % [at.name_with_size])
end
source.puts('} *%s;' % [tad_name + 'Ptr'])
source.puts('')
source.puts('%s {' %[creator])
source.puts('    %sPtr %s = malloc(sizeof(struct %s_t));' % [tad_name, downcase_tad_name, downcase_tad_name])
attributes.each do |at|
    next if !at.required
    if at.size != nil
        source.puts('    strcpy(%s->%s, %s);' % [downcase_tad_name, at.name, at.name])
    else
        source.puts('    %s->%s = %s;' % [downcase_tad_name, at.name, at.name])
    end
end
source.puts('    return %s;' % [downcase_tad_name])
source.puts('}')
void_to_ptr = '%sPtr %s = (%sPtr) %sVoid' % [tad_name, downcase_tad_name, tad_name, downcase_tad_name]
getters.each.with_index do |at, i|
    source.puts('')
    source.puts('%s {' %[getters[i]])
    source.puts('    %s;' %[void_to_ptr])
    source.puts('    return %s->%s;' % [downcase_tad_name, attributes[i].name])
    source.puts('}')
end

setters.each.with_index do |at, i|
    source.puts('')
    source.puts('%s {' %[setters[i]])
    source.puts('    %s;' %[void_to_ptr])
    if attributes[i].size != nil
        source.puts('    strcpy(%s->%s, %s);' % [downcase_tad_name, attributes[i].name, attributes[i].name])
    else
        source.puts('    %s->%s = %s;' % [downcase_tad_name, attributes[i].name, attributes[i].name])
    end
    source.puts('}')
end
source.close